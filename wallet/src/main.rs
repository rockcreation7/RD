use axum::{response::Html, routing::get, Router};

#[tokio::main]
async fn main() {
    // build our application with a route
    let app = Router::new().route("/", get(handler));

    // run it
    axum::Server::bind(&"127.0.0.1:80".parse().unwrap())
        .serve(app.into_make_service())
        .await
        .unwrap();
    // println!("listening on {}", listener.local_addr().unwrap());
    // axum::serve(app).await.unwrap();
}

async fn handler() -> Html<&'static str> {
    Html("<h1>Hello, World!</h1>")
}
