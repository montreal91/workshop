
mod generated;

use crate::generated::HelloService::HelloRequest;
use crate::generated::HelloService::HelloResponse;
use crate::generated::HelloService_grpc::HelloServiceClient;

use grpc::ClientStubExt;
use futures::executor;
use grpc::Metadata;
use grpc::Error;


fn extract_response(result: &Result<(Metadata, HelloResponse, Metadata), Error>) -> String {
    match result {
        Ok(result) => {
            println!("Ok");
            let x = result.1.clone();
            x.greeting
        }
        Err(e) => {
            panic!("An Error Returned {:?}", e);
        }
    }

}


fn main() {
    let name = "Raphael";
    let surname = "Nadal";
    let client_conf = Default::default();

    let client = HelloServiceClient::new_plain("localhost", 8080, client_conf).unwrap();

    let mut request = HelloRequest::new();
    request.set_firstName(name.to_string());
    request.set_lastName(surname.to_string());

    let response = client.hello(grpc::RequestOptions::new(), request).join_metadata_result();

    println!("{:?}", extract_response(&executor::block_on(response)));
}
