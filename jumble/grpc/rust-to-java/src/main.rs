
use grpc::hello_service_client::HelloServiceClient;
use grpc::HelloRequest;

pub mod grpc {
    tonic::include_proto!("com.mycompany.app.grpc");
}


#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let request = tonic::Request::new(
        HelloRequest {
            first_name: String::from("Novak"),
            last_name: String::from("Djokovic"),
        },
    );
    let mut client = HelloServiceClient::connect("http://localhost:8080").await?;

    let response = client.hello(request).await?;
    println!("RESPONSE={:?}", response.get_ref().greeting);

    Ok(())
}
