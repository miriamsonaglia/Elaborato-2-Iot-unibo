package src;

import com.fazecast.jSerialComm.SerialPort;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class OperatorDashboard {

    public static void main(String[] args) {
        // Configurazione della porta seriale. 
        // Apro una connessione con la porta specifica
        SerialPort serialPort = SerialPort.getCommPort("COM3"); // COM3 è la porta. Da cambiare in base alla porta giusta
        serialPort.setBaudRate(9600);

        // Tento di aprire la connessione con la seriale
        // Se la connessione non riesce (perchè la porta è occupata o inesistente) va in errore e il programma termina
        if (!serialPort.openPort()) {
            JOptionPane.showMessageDialog(null, "Errore: impossibile aprire la porta seriale.", "Errore", JOptionPane.ERROR_MESSAGE);
            return;
        }

        // Finestra principale
        JFrame frame = new JFrame("Operator Dashboard");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 400);
        frame.setLayout(new BorderLayout());

        // Panel per lo stato del container
        JPanel statusPanel = new JPanel();
        statusPanel.setLayout(new GridLayout(3, 2, 10, 10));
        statusPanel.setBorder(BorderFactory.createTitledBorder("Container Status"));

        // Etichette e valori di stato          I VALORI VANNO LETTI, ME LI DA ARDUINO TRAMITE IL THREAD
        JLabel wasteLevelLabel = new JLabel("Filling Percentage:");
        JLabel wasteLevelValue = new JLabel("0%");      //VA LETTO

        JLabel temperatureLabel = new JLabel("Temperature:");
        JLabel temperatureValue = new JLabel("22°C");   //VA LETTO

        JLabel statusLabel = new JLabel("Status:");
        JLabel statusValue = new JLabel("Available");   //VA LETTO
        
        // Aggiungo le etichette al Panel
        statusPanel.add(wasteLevelLabel);
        statusPanel.add(wasteLevelValue);
        statusPanel.add(temperatureLabel);
        statusPanel.add(temperatureValue);
        statusPanel.add(statusLabel);
        statusPanel.add(statusValue);

        // Panel per i pulsanti
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new GridLayout(1, 2, 10, 10));
        buttonPanel.setBorder(BorderFactory.createTitledBorder("Operator actions"));

        // Quando premo uno dei pulsanti della GUI, viene inviato un messaggio all'Arduino
        JButton emptyButton = new JButton("EMPTY THE CONTAINER");
        emptyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (serialPort.isOpen()) {      // Controllo se la seriale è aperta
                    // Invia la stringa "EMPTY" come comando alla seriale,
                    // Arduino deve leggere iol comando e reagire di conseguenza
                    serialPort.writeBytes("EMPTY\n".getBytes(), "EMPTY\n".length());
                }
            }
        });

        // Stessa cosa di EMPTY ma comando diverso (RESTORE)
        JButton restoreButton = new JButton("RESTORE");
        restoreButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (serialPort.isOpen()) {
                    serialPort.writeBytes("RESTORE\n".getBytes(), "RESTORE\n".length());
                }
            }
        });

        // Aggiungo i pulsanti al pannello
        buttonPanel.add(emptyButton);
        buttonPanel.add(restoreButton);

        // Aggiungo i Panel alla finestra principale
        frame.add(statusPanel, BorderLayout.CENTER);
        frame.add(buttonPanel, BorderLayout.SOUTH);

        // Thread per ricevere i dati dalla seriale
        // Legge continuamente i dati ricevuti dall'Arduino tramite la seriale
        Thread readThread = new Thread(() -> {
            byte[] buffer = new byte[1024];  // Definisco un area di memoria per memorizzare i dati
            while (serialPort.isOpen()) {
                int bytesRead = serialPort.readBytes(buffer, buffer.length); // Legge i dati disponibili e li salva nel buffer
                if (bytesRead > 0) {    // Se il numero di bytes letti > 0, li converte in una Stringa
                    String data = new String(buffer, 0, bytesRead).trim();
                    // Aggiorno lo stato del container in tempo reale
                    SwingUtilities.invokeLater(() -> {
                        if (data.startsWith("STATUS:")) {
                            // Parsing dei dati ricevuti
                            String[] parts = data.substring(7).split(" ");
                            for (String part : parts) {
                                if (part.startsWith("Filling:")) {
                                    wasteLevelValue.setText(part.split(":")[1]);
                                } else if (part.startsWith("Temperature:")) {
                                    temperatureValue.setText(part.split(":")[1]);
                                }
                            }
                        // Aggiorno lo stato del container in base al pulsante che ho premuto
                        } else if (data.equals("Container emptied")) {
                            statusValue.setText("Available");
                            wasteLevelValue.setText("0%");
                        } else if (data.equals("Container restored")) {
                            statusValue.setText("Available");
                        }
                    });
                }
            }
        });
        readThread.start();

        // Rendo la finestra visibile
        frame.setVisible(true);
    }
}
