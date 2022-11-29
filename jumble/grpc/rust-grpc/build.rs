
fn main() {
    protoc_rust_grpc::Codegen::new()
        .out_dir("src/generated")
        .input("proto/HelloService.proto")
        .rust_protobuf(true)
        .run()
        .expect("Error compiling protocol buffer.");
}
