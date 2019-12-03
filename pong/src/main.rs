use sdl2::keyboard::Keycode;
use sdl2::rect::Rect;

use std::error::Error;
use std::time::{Duration, Instant};

enum paddle_direction {
    Up,
    Down,
}

const PADDLE_MOV: i32 = 20;

struct pong_data {
    player1: Rect,
    player2: Rect,

    ball: Rect,
}

impl pong_data {
    // initialize default state for the game
    fn new() -> pong_data {
        pong_data {
            player1: Rect::new(20, 250, 20, 100),
            player2: Rect::new(850, 250, 20, 100),
            ball: Rect::new(450, 300, 20, 20),
        }
    }

    // makes sure the rect is in bounds.
    fn correct_position(rect: Rect) -> Rect {
        let y: i32;
        
        if rect.y >= (900 - 100) {
            y = 900 - 100;
        } else if rect.y <= (0 + 100) {
            y = 100;
        } else {
            y = rect.y;
        }

        Rect::new(rect.x, y, rect.width(), rect.height())
    }

    // moves the player
    fn move_player(&mut self, dir: paddle_direction) {
        match dir {
            paddle_direction::Up => self.player1.y += PADDLE_MOV,
            paddle_direction::Down => self.player1.y -= PADDLE_MOV,
        }

        self.player1 = pong_data::correct_position(self.player1);
    }

    // runs the game simulation
    fn simulate(&mut self) {}
}

struct sdl_data {
    // both of these are in the sdl_data so they don't get destroyed until the game ends
    context: sdl2::Sdl,
    video_subsystem: sdl2::VideoSubsystem,

    // usable data
    canvas: sdl2::render::Canvas<sdl2::video::Window>,
    event_pump: sdl2::EventPump,
}

impl sdl_data {
    fn new() -> Result<sdl_data, Box<dyn Error>> {
        let new_context = sdl2::init()?;
        let new_vsubsystem = new_context.video()?;
        let new_window = new_vsubsystem
            .window("Pong", 900, 600)
            .position_centered()
            .build()?;

        let new_canvas = new_window.into_canvas().build()?;
        let new_event_pump = new_context.event_pump()?;

        Ok(sdl_data {
            context: new_context,
            video_subsystem: new_vsubsystem,
            canvas: new_canvas,
            event_pump: new_event_pump,
        })
    }

    // renders the entire game
    fn draw_window(&mut self, pdata: &pong_data) {
        // clear the screen
        self.canvas
            .set_draw_color(sdl2::pixels::Color::RGB(0, 0, 0));
        self.canvas.clear();

        // render the pong_data
        self.canvas.set_draw_color(sdl2::pixels::Color::RGB(255, 255, 255));
        let _ = self.canvas.fill_rect(pdata.player1);
        
        self.canvas.present();
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    println!("Initializing SDL2...");

    let mut game_data = sdl_data::new()?;
    let mut pdata = pong_data::new();

    let mut frame_time: Instant;

    let frame_duration: f32 = 1000f32 / 15f32;

    println!("SDL is done initializing");

    'run: loop {
        frame_time = Instant::now();

        for event in game_data.event_pump.poll_iter() {
            // handle events
            match event {
                sdl2::event::Event::Quit { .. } => break 'run,
                sdl2::event::Event::KeyDown { keycode: Some(Keycode::Down), ..  } => pdata.move_player(paddle_direction::Down),
                _ => {}
            }
        }

        // simulation
        pdata.simulate();

        // frame control

        // TODO
        let duration = frame_time.elapsed().as_nanos();

        if frame_duration > duration as f32 {
            let wait_time_millis = frame_duration - duration as f32;

            let delta_duration = Duration::from_millis(wait_time_millis as u64);

            std::thread::sleep(delta_duration);
        }

        // draw
        game_data.draw_window(&pdata);
    }

    println!("Exiting the game...");
    Ok(())
}
