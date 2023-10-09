package com.clientserver.tcp;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

    public static void main(String[] args) throws IOException {
        // Inizializza una socket TCP che accetta connessioni da parte dei client
        ServerSocket serverSocket = new ServerSocket(8080);

        // Aggiungi un gestore di interruzione (chiude il server socket quando faccio CTRL+C)
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            try {
                // Chiude il server socket
                serverSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }));

        while (true) { // Gestisce molteplici client creando un thread e un socket diverso per ognuno di essi
            // Accetta una connessione da un client
            Socket socket = serverSocket.accept();

            // Crea un thread per gestire la connessione
            Thread thread = new Thread(() -> {
                try (// Legge la richiesta dal client
                InputStream input = socket.getInputStream()) {
                    byte[] bytes = new byte[input.available()];
                    input.read(bytes);
                    String request = new String(bytes);

                    // Esegue la richiesta
                    String response = "";
                    if (request.equals("conversione")) {
                        // Converte una stringa in maiuscolo
                        response = request.toUpperCase();
                    }

                    // Invia la risposta al client
                    OutputStream output = socket.getOutputStream();
                    output.write(response.getBytes());
                } catch (IOException e) {
                    e.printStackTrace();
                }
                // Chiude il socket
                try {
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                
            });

            thread.start();
        }
    }
}