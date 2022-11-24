
use tonic::{transport::Server, Request, Response, Status};
use api::say_server::{Say, SayServer};
use api::{SayResponse, SayRequest};

pub mod api {
    tonic::include_proto!("hello");
}

#[derive(Default)]
pub struct MySay {}

#[tonic::async_trait]
impl Say for MySay {
    async fn send(&self, request:Request<SayRequest>) -> Result<Response<SayResponse>, Status> {
        println!("Got name: {}", request.get_ref().name);
        Ok(Response::new(SayResponse { message: format!("hello {}", request.get_ref().name) }))
    }
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    println!("GRPC!");
    let addr = "[::1]:50051".parse().unwrap();
    let say = MySay::default();
    println!("Server listening on {}", addr);
    Server::builder().add_service(SayServer::new(say)).serve(addr).await?;
    Ok(())
}
