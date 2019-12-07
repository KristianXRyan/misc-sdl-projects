use sdl2::keyboard::Keycode;
use sdl2::rect::Rect;

use std::error::Error;
use std::time::{Duration, Instant, SystemTime, UNIX_EPOCH};

#[repr(usize)]
enum NumType {
    P1Score = 0,
    P2Score = 1,
    FPS = 2,
}

enum PaddleDuration {
    Up,
    Down,
}

enum PlayerNum {
    P1,
    P2,
    None,
}

const PADDLE_MOV: i32 = 10;

struct Ball {
    location: Rect,
    dx: i32,
    dy: i32,
}

impl Ball {
    const DEFAULT_POS: (i32, i32) = (450, 300);
    
    // inits a ball
    fn new() -> Self {
        let (dx, dy) = Self::reset_delta();
        let (x, y) = Self::DEFAULT_POS;

        Self {
            location: Rect::new(x, y, 10, 10),
            dx: dx,
            dy: dy,
        }
    }

    // bounces the ball (reverses its delta y and sometimes its delta x)
    fn bounce(&mut self, on_x: bool) {
        self.dy = -self.dy;

        if on_x {
            self.dx = -self.dx;
        }
    }

    // checks if the ball is colliding with a paddle
    fn check_collision_and_bounce(&mut self, rect: &Rect) {
        if rect.intersection(self.location) != None {
            self.bounce(true);
        }
    }

    fn reset(&mut self) {
        self.location.x = Self::DEFAULT_POS.0;
        self.location.y = Self::DEFAULT_POS.1;

        let deltas = Self::reset_delta();

        self.dx = deltas.0;
        self.dy = deltas.1;
    }

    // sets new dx and dy values
    fn reset_delta() -> (i32, i32) {
        let dy: i32;
        let dx: i32;

        // random number generator. takes the time from the epoch in nanoseconds
        // and performs modulo on it. return either 1 or -1.
        let positive_or_negative = || -> i32 {

            let nanos = SystemTime::now()
                .duration_since(UNIX_EPOCH)
                .unwrap()
                .subsec_nanos();

            let result = nanos as i32 % 2;

            if result == 1 {
                return 1;
            }
            -1
        };

        dx = 3 * positive_or_negative();
        dy = 3 * positive_or_negative();

        (dx, dy)
    }

    // moves the ball around the screen. returns the player that scored.
    fn simulate(&mut self, rect1: &Rect, rect2: &Rect) -> PlayerNum {
        let mut player = PlayerNum::None;

        // move the ball
        self.location.set_x(self.location.x() + self.dx);
        self.location.set_y(self.location.y() + self.dy);

        // check to make sure it has not gone out of bounds.
        // if it has, then bounce.

        if self.location.x >= 900 {
            player = PlayerNum::P1;
        } else if self.location.x <= 0 {
            player = PlayerNum::P2;
        }

        if self.location.y >= 600 {
            self.bounce(false);
        } else if self.location.y <= 0 {
            self.bounce(false);
        }

        match player {
            PlayerNum::None => {
                self.check_collision_and_bounce(rect1);
                self.check_collision_and_bounce(rect2);
            }

            _ => {}
        }

        player
    }
}

struct PongData {
    player1: Rect,
    player2: Rect,

    ball: Ball,

    player1_score: u32,
    player2_score: u32,
}

impl PongData {
    // initialize default state for the game
    fn new() -> Self {
        Self {
            player1: Rect::new(20, 250, 20, 100),
            player2: Rect::new(850, 250, 20, 100),
            ball: Ball::new(),
            player1_score: 0,
            player2_score: 0,
        }
    }

    // makes sure the rect is in bounds.
    fn correct_position(rect: &mut Rect) {
        let y: i32;

        if rect.y <= 0 {
            y = 0;
        } else if rect.y >= 500 {
            y = 500;
        } else {
            y = rect.y;
        }

        rect.y = y;
    }

    // moves the player
    fn move_player(dir: PaddleDuration, player: &mut Rect) {
        match dir {
            PaddleDuration::Up => player.y -= PADDLE_MOV,
            PaddleDuration::Down => player.y += PADDLE_MOV,
        }

        PongData::correct_position(player);
    }

    // runs the game simulation (AI and moving the ball)
    fn simulate(&mut self) {
        match self.ball.simulate(&self.player1, &self.player2) {
            PlayerNum::P1 => {
                self.player1_score += 1;
                self.ball.reset();
                return;
            }

            PlayerNum::P2 => {
                self.player2_score += 1;
                self.ball.reset();
                return;
            }

            PlayerNum::None => {}
        }

        // move the AI's paddle
        if self.ball.location.y >= self.player2.y + 15 {
            PongData::move_player(PaddleDuration::Down, &mut self.player2);
        } else if self.ball.location.y <= self.player2.y + 15 {
            PongData::move_player(PaddleDuration::Up, &mut self.player2);
        }
    }
}

struct SDLData<'a> {
    context: sdl2::Sdl,
    video_subsystem: sdl2::VideoSubsystem,

    // usable data
    canvas: sdl2::render::Canvas<sdl2::video::Window>,
    event_pump: sdl2::EventPump,
    ttf_context: sdl2::ttf::Sdl2TtfContext,

    // parallel arrays representing text areas

    // item 1: player 1 score
    // item 2: player 2 score
    // item 3: fps
    drawables: [Option<sdl2::surface::Surface<'a>>; 3],
    drawables_location: [Option<Rect>; 3],
}

impl<'a> SDLData<'a> {
    fn new() -> Result<SDLData<'a>, Box<dyn Error>> {
        let new_context = sdl2::init()?;
        let new_vsubsystem = new_context.video()?;
        let new_window = new_vsubsystem
            .window("Pong", 900, 600)
            .position_centered()
            .opengl()
            .build()?;

        let new_canvas = new_window.into_canvas().build()?;
        let new_event_pump = new_context.event_pump()?;

        let new_ttf_context = sdl2::ttf::init()?;

        Ok(SDLData {
            context: new_context,
            video_subsystem: new_vsubsystem,
            canvas: new_canvas,
            event_pump: new_event_pump,
            ttf_context: new_ttf_context,

            drawables: [None, None, None],
            drawables_location: [None, None, None],
        })
    }

    // renders the entire game
    fn draw_window(&mut self, pdata: &PongData) -> Result<(), Box<dyn Error>> {
        // clear the screen
        self.canvas
            .set_draw_color(sdl2::pixels::Color::RGB(0, 0, 0));
        self.canvas.clear();

        // render the PongData
        self.canvas
            .set_draw_color(sdl2::pixels::Color::RGB(255, 255, 255));
        let _ = self.canvas.fill_rect(pdata.player1);
        let _ = self.canvas.fill_rect(pdata.player2);
        let _ = self.canvas.fill_rect(pdata.ball.location);

        // render the board
        let net: Rect = Rect::new(445, 0, 10, 600);
        let _ = self.canvas.draw_rect(net);

        for item in 0..self.drawables.len() {
            match &self.drawables[item] {
                Some(x) => {
                    self.canvas.copy(
                        &self
                            .canvas
                            .texture_creator()
                            .create_texture_from_surface(&x)?,
                        None,
                        Some(self.drawables_location[item].unwrap()),
                    )?;
                }

                None => {}
            }
        }
        self.canvas.present();

        Ok(())
    }

    // draws a number as text to the screen
    fn draw_number(
        &mut self,
        num: i32,
        where_to: Rect,
        num_meaning: NumType,
    ) -> Result<(), Box<dyn Error>> {
        // rust won't let me wrap this in a struct...
        let mut font = self.ttf_context.load_font("arial.ttf", 16)?;
        font.set_style(sdl2::ttf::FontStyle::BOLD);

        let surface = font
            .render(num.to_string().as_str())
            .blended(sdl2::pixels::Color::RGBA(255, 0, 0, 255))?;

        let index = num_meaning as usize;

        self.drawables[index] = Some(surface);
        self.drawables_location[index] = Some(where_to);

        Ok(())
    }
}

// main
fn main() -> Result<(), Box<dyn Error>> {
    println!("Initializing SDL2...");

    let mut game_data = SDLData::new()?;
    let mut pdata = PongData::new();

    // framerate control structs
    let mut start_frame_time: Instant;
    let mut start_second_time: Instant = Instant::now();
    let mut frame_render_time: Duration;
    let mut frames: i32 = 0;
    let show_frame_rate: bool = should_render_framerate();

    const FRAME_TIME: f32 = 1000f32 / 60f32;
    const ONE_SECOND: Duration = Duration::from_millis(1000);

    println!("SDL is done initializing");

    'run: loop {
        start_frame_time = Instant::now();

        for event in game_data.event_pump.poll_iter() {
            // handle events
            match event {
                sdl2::event::Event::Quit { .. } => break 'run,
                sdl2::event::Event::KeyDown {
                    keycode: Some(Keycode::Down),
                    ..
                } => PongData::move_player(PaddleDuration::Down, &mut pdata.player1),

                sdl2::event::Event::KeyDown {
                    keycode: Some(Keycode::Up),
                    ..
                } => PongData::move_player(PaddleDuration::Up, &mut pdata.player1),
                _ => {}
            }
        }

        // simulation
        pdata.simulate();

        // frame control
        frame_render_time = Instant::now() - start_frame_time;

        if FRAME_TIME > frame_render_time.as_millis() as f32 {
            frames += 1;

            let sleep_time: Duration =
                Duration::from_millis((FRAME_TIME as u128 - frame_render_time.as_millis()) as u64);

            std::thread::sleep(sleep_time);
        }

        // for keeping track of the frame rate. runs once a second.
        if start_second_time.elapsed() >= ONE_SECOND {
            // render the framerate
            if show_frame_rate {
                game_data.draw_number(frames, Rect::new(850, 0, 50, 50), NumType::FPS)?;
            }

            frames = 0;
            start_second_time = Instant::now();
        }

        game_data.draw_number(
            pdata.player1_score as i32,
            Rect::new(325, 30, 50, 50),
            NumType::P1Score,
        )?;

        game_data.draw_number(
            pdata.player2_score as i32,
            Rect::new(500, 30, 50, 50),
            NumType::P2Score,
        )?;
        // draw
        game_data.draw_window(&pdata)?;
    }

    println!("Exiting the game...");
    Ok(())
}

// determines if the user wants to see the framerate
fn should_render_framerate() -> bool {
    let args: Vec<String> = std::env::args().collect();

    for i in 1..args.len() {
        if "--frate" == args[i] {
            return true;
        }
    }

    false
}
