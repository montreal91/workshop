
fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("Tonic-Build!");
    tonic_build::compile_protos("proto/hello.proto")?;
    Ok(())
}
