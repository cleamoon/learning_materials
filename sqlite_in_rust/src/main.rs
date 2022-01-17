extern crate clap;
mod repl;

use repl::{REPLHelper, get_config};
use rustyline::error::ReadlineError;
use rustyline::Editor;
use clap::{App, crate_version};

fn main() -> rustyline::Result<()> {
    env_logger::init();

    let _matches = App::new("SQLite in Rust")
        .version("0.0.1")
        .author("Yue Jiao")
        .about("Light version of SQLite developed with Rust")
        .get_matches();

    let config = get_config();
    let helper = REPLHelper::new();

    let mut repl = Editor::with_config(config);
    repl.set_helper(Some(helper));

    if repl.load_history("history").is_err() {
        println!("No previous history");
    }

    let mut count = 1;
    loop {
        if count == 1 {
            println!("{}{}{}{}{}",
            format!("SQLite in Rust - {}\n", crate_version!()),
            "Enter .exit to quit.\n",
            "Enter .help to usage hints.\n",
            "Connected to a transient in-memory database.\n",
            "Use '.open Filename' to reopen on a persistent database.");
        }

        let p = format!("sqlite-in-rust | {}> ", count);
        repl.helper_mut()
            .expect("No helper found")
            .colored_prompt = format!("\x1b[1;32m{}\x1b[0m", p);

        let readline = repl.readline(&p);
        match readline {
            Ok(command) => {
                repl.add_history_entry(command.as_str());
                //println!("Line: {}", line);
                if command.eq(".exit") {
                    break;
                } else {
                    println!("Error: unknown command or invalid arguments: '{}'. Enter '.help' for help", &command);
                }
            },
            Err(ReadlineError::Interrupted) => {
                println!("CTRL-C");
                break
            },
            Err(ReadlineError::Eof) => {
                println!("CTRL-D");
                break
            },
            Err(err) => {
                println!("Error: {:?}", err);
                break
            }
        }
        count += 1;
    }

    repl.save_history("history").unwrap();

    Ok(())
}
