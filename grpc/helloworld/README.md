# gRPC Hello World

Follow these setup to run the [quick start][] example:

 1. Get the code:

    ```console
    $ go get google.golang.org/grpc/examples/helloworld/greeter_client
    $ go get google.golang.org/grpc/examples/helloworld/greeter_server
    ```

 2. Run the server:

    ```console
    $ go run greeter_server/main.go
    ```

 3. Run the client:

    ```console
    $ go run greeter_client/main.go 
    Greeting: Hello world
    ```

For more details (including instructions for making a small change to the
example code) or if you're having trouble running this example, see [Quick
Start][].

[quick start]: https://grpc.io/docs/languages/go/quickstart


Update proto
Add Your Go Path
1. export PATH="$PATH:$(go env GOPATH)/bin" << zsh
2. protoc --go_out=. --go_opt=paths=source_relative \
    --go-grpc_out=. --go-grpc_opt=paths=source_relative \
    helloworld/helloworld.proto