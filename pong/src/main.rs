use sdl2::keyboard::Keycode;
use sdl2::rect::Rect;

use std::error::Error;
use std::time::{Duration, Instant};

enum PaddleDuration {
    Up,
    Down,
}

const PADDLE_MOV: i32 = 20;

struct PongData {
    player1: Rect,
    player2: Rect,

    ball: Rect,

    player1_score: u32,
    player2_score: u32,
}

impl PongData {
    // initialize default state for the game
    fn new() -> PongData {
        PongData {
            player1: Rect::new(20, 250, 20, 100),
            player2: Rect::new(850, 250, 20, 100),
            ball: Rect::new(450, 300, 10, 10),
            player1_score: 0,
            player2_score: 0,
        }
    }

    // makes sure the rect is in bounds.
    fn correct_position(rect: Rect) -> Rect {
        let y: i32;

        if rect.y <= 0 {
            y = 0;
        } else if rect.y >= 800 {
            y = 800;
        } else {
            y = rect.y;
        }

        Rect::new(rect.x, y, rect.width(), rect.height())
    }

    // moves the player
    fn move_player(&mut self, dir: PaddleDuration) {
        match dir {
            PaddleDuration::Up => self.player1.y -= PADDLE_MOV,
            PaddleDuration::Down => self.player1.y += PADDLE_MOV,
        }

        self.player1 = PongData::correct_position(self.player1);
    }

    // runs the game simulation
    fn simulate(&mut self) {}
}

struct SDLData {
    // both of these are in the SDLData  so they don't get destroyed until the game ends
    context: sdl2::Sdl,
    video_subsystem: sdl2::VideoSubsystem,

    // usable data
    canvas: sdl2::render::Canvas<sdl2::video::Window>,
    event_pump: sdl2::EventPump,
}

impl SDLData  {
    fn new() -> Result<SDLData , Box<dyn Error>> {
        let new_context = sdl2::init()?;
        let new_vsubsystem = new_context.video()?;
        let new_window = new_vsubsystem
            .window("Pong", 900, 600)
            .position_centered()
            .build()?;

        let new_canvas = new_window.into_canvas().build()?;
        let new_event_pump = new_context.event_pump()?;

        Ok(SDLData  {
            context: new_context,
            video_subsystem: new_vsubsystem,
            canvas: new_canvas,
            event_pump: new_event_pump,
        })
    }

    // renders the entire game
    fn draw_window(&mut self, pdata: &PongData) {
        // clear the screen
        self.canvas
            .set_draw_color(sdl2::pixels::Color::RGB(0, 0, 0));
        self.canvas.clear();

        // render the PongData
        self.canvas
            .set_draw_color(sdl2::pixels::Color::RGB(255, 255, 255));
        let _ = self.canvas.fill_rect(pdata.player1);
        let _ = self.canvas.fill_rect(pdata.player2);
        let _ = self.canvas.fill_rect(pdata.ball);

        // render the board
        let net: Rect = Rect::new(445, 0, 10, 600);
        let _ = self.canvas.draw_rect(net);

        self.canvas.present();
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    println!("Initializing SDL2...");

    let mut game_data = SDLData ::new()?;
    let mut pdata = PongData::new();

    // framerate control structs
    let mut start_frame_time: Instant;
    let mut start_second_time: Instant = Instant::now();
    let mut frame_render_time: Duration;
    let mut frames: i32 = 0;

    const FRAME_TIME: f32 = 1000f32 / 30f32;
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
                } => pdata.move_player(PaddleDuration::Down),

                sdl2::event::Event::KeyDown {
                    keycode: Some(Keycode::Up),
                    ..
                } => pdata.move_player(PaddleDuration::Up),
                _ => {}
            }
        }

        // simulation
        pdata.simulate();

        // frame control
        frame_render_time = Instant::now() - start_frame_time;

        if FRAME_TIME > frame_render_time.as_millis() as f32 {
            frames += 1;

            let sleep_time: Duration = Duration::from_millis((FRAME_TIME as u128 - frame_render_time.as_millis()) as u64);

            std::thread::sleep(sleep_time);
        }

        if start_second_time.elapsed() >= ONE_SECOND {
            println!("{}", frames);
            frames = 0;
            start_second_time = Instant::now();
        }

        // draw
        game_data.draw_window(&pdata);
    }

    println!("Exiting the game...");
    Ok(())
}
