package main

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"net/http"
)

func main() {
	//http.Handle("/foo", fooHandler)
	port := "8080"
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		//fmt.Fprintf(w, "Hello, %q", html.EscapeString(r.URL.Path))
		/* v := r.Body */

		b, err := ioutil.ReadAll(r.Body)
		if err != nil {
			panic(err)
		}
		log.Println("body:", string(b))

		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]interface{}{
			"success": true,
		})
		/* fmt.Fprintf(w, `{"url" : %q}`, html.EscapeString(r.URL.Path)) */
	})

	log.Println("Listen And Serve -", port)

	log.Fatal(http.ListenAndServe(":"+port, nil))
}
