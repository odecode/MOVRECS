package main

import (
	"net/http"
	"os/exec"
	"log"
	"strings"
)

func calculateHandler(w http.ResponseWriter, r *http.Request) {
	// Extract user ID from URL path
	parts := strings.Split(r.URL.Path, "/")
	if len(parts) < 3 {
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte("Missing user ID"))
		return
	}
	userID := parts[2]

	// Run the C++ executable with usernum argument
	cmd := exec.Command("./recommender", "usernum", userID)
	output, err := cmd.Output()
	if err != nil {
		log.Printf("Error running C++ executable: %v", err)
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("Error running calculation"))
		return
	}
	w.WriteHeader(http.StatusOK)
	w.Write(output)
}

func main() {
	http.HandleFunc("/calculate/", calculateHandler)
	log.Println("Server running on :8080")
	if err := http.ListenAndServe(":8080", nil); err != nil {
		log.Fatalf("Server failed: %v", err)
	}
}
