package main

import (
	"context"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"os/signal"
	"syscall"
	"time"

	_ "github.com/lib/pq"
)

func getRoot(w http.ResponseWriter, r *http.Request) {
	fmt.Printf("got / request\n")
	io.WriteString(w, "This is my website 2!\n")
}

func getHello(w http.ResponseWriter, r *http.Request) {
	hasFirst := r.URL.Query().Has("first")
	fmt.Println("got /hello request\n", hasFirst, r.Method)

	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		fmt.Printf("could not read body: %s\n", err)
	}
	var req map[string]interface{}
	json.Unmarshal(body, &req)

	fmt.Println("got /hello request\n", string(body), req["Hello"])
	json.NewEncoder(w).Encode(map[string]interface{}{
		"Hello": 123,
	})
}

func main() {

	/* // Connection parameters
	host := "localhost"
	port := 5432
	user := "postgres"
	password := "mysecretpassword"
	dbname := "demo"

	// Construct the connection string
	connStr := fmt.Sprintf("host=%s port=%d user=%s password=%s dbname=%s sslmode=disable", host, port, user, password, dbname)

	// Open a database connection
	db, err := sql.Open("postgres", connStr)
	if err != nil {
		panic(err)
	}
	defer db.Close()

	db.SetMaxOpenConns(5)
	db.SetMaxIdleConns(5)

	// Check if the connection is successful
	err = db.Ping()
	if err != nil {
		panic(err)
	}

	fmt.Println("Connected to the PostgreSQL database!")

	// SQL query
	query := "SELECT * FROM Customers"

	// Execute the query
	rows, err := db.Query(query)
	if err != nil {
		panic(err)
	}
	defer rows.Close()

	// Iterate over the result rows
	for rows.Next() {
		var PersonID sql.NullInt16
		var CustomerName string
		var ContactName string
		var Address string
		var City string
		var PostalCode string
		var Country string

		// Scan the row into variables
		err := rows.Scan(&PersonID, &CustomerName, &ContactName, &Address, &City, &PostalCode, &Country)
		if err != nil {
			panic(err)
		}

		// Do something with the retrieved data
		fmt.Println(PersonID, CustomerName, ContactName, Address, City, PostalCode, Country)
	}

	if err = rows.Err(); err != nil {
		panic(err)
	}
	*/
	mux := http.NewServeMux()

	mux.HandleFunc("/", getRoot)
	mux.HandleFunc("/hello", getHello)

	server := &http.Server{
		Addr:    ":8080",
		Handler: mux,
	}

	go func() {
		if err := server.ListenAndServe(); !errors.Is(err, http.ErrServerClosed) {
			log.Fatalf("HTTP server error: %v", err)
		}
		log.Println("Stopped serving new connections.")
	}()

	sigChan := make(chan os.Signal, 1)
	signal.Notify(sigChan, syscall.SIGINT, syscall.SIGTERM)
	<-sigChan

	shutdownCtx, shutdownRelease := context.WithTimeout(context.Background(), 10*time.Second)
	defer shutdownRelease()

	if err := server.Shutdown(shutdownCtx); err != nil {
		log.Fatalf("HTTP shutdown error: %v", err)
	}
	log.Println("Graceful shutdown complete.")
}
