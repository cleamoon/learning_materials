// https://notes.eatonphil.com/lua-in-rust.html

mod eval;
mod lex;
mod parse;

use std::env;
use std::fs;

fn main() {
    let args: Vec<String> = env::args().collect();
    let contents = fs::read_to_string(&args[1]).expect("Count not read file ");

    let raw: Vec<char> = contents.chars().collect();

    let tokens = match lex::lex(&raw) {
	Ok(tokens) => tokens,
	Err(msg) => panic!("{}", msg),
    };

    let ast = match parse::parse(&raw, tokens) {
	Ok(ast) => ast,
	Err(msg) => panic!("{}", msg),
    };

    let pgrm = eval::compile(&raw, ast);

    eval::eval(pgrm);
}
