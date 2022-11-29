
use api::say_client::SayClient;
use api::SayRequest;

pub mod api {
    tonic::include_proto!("hello");
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let request = tonic::Request::new(
        SayRequest {
            name:String::from("Vova")
        },
    );
    let mut client = SayClient::connect("http://[::1]:50051").await?;

    let response = client.send(request).await?;
    println!("RESPONSE={:?}", response.get_ref().message);

    Ok(())
}
