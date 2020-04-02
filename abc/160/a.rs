fn main() {
    let mut buffer = String::new();
    std::io::stdin().read_line(&mut buffer).unwrap();
    let bytes = buffer.as_bytes();
    if &bytes[2] == &bytes[3] && &bytes[4] == &bytes[5] {
        println!("Yes");
    }
    else {
        println!("No");
    }
}