
use std::error::Error;
use std::fs::File;
use std::io::prelude::*;

const QUERY_INDEX: usize = 1;
const FILENAME_INDEX: usize = 2;
const MIN_ARG_LEN: usize = 3;

pub struct Config {
  pub query: String,
  pub filename: String,
}

// fn parse_config(args: &[String]) -> Config {
// }

impl Config {
  pub fn new(args: &[String]) -> Result<Config, &'static str> {
    if args.len() < MIN_ARG_LEN {
      panic!("Not enough arguments!");
    }
    let query = args[QUERY_INDEX].clone();
    let filename = args[FILENAME_INDEX].clone();

    return Ok(Config {query, filename});
  }
}

pub fn run(config: Config) -> Result<(), Box<Error>> {
  // let mut f = File::open(confi)
  let mut f = File::open(config.filename)?;
    // .expect("File not found.");

  let mut contents = String::new();

  f.read_to_string(&mut contents).expect("Something went wrong reading the file.");

  println!("With text:\n{}", contents);

  return Ok(());
}
