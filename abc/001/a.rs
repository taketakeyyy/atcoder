use std::io::*;
use std::str::FromStr;

fn input<T: FromStr>() -> T {
    let stdin = stdin();
    let stdin = stdin.lock();
    let token: String = stdin
        .bytes()
        .map(|c| c.expect("failed to read char") as char)
        .skip_while(|c| c.is_whitespace())
        .take_while(|c| !c.is_whitespace())
        .collect();
    token.parse().ok().expect("failed to parse token")
}

fn main(){
    // 読み込み
    let h1: i32 = input();
    let h2: i32 = input();
    // 出力
    println!("{}", h1-h2);
}