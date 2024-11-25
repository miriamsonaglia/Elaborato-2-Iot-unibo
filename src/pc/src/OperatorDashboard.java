package src;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class OperatorDashboard {

    public static void main(String[] args) {
        // Finestra principale
        JFrame frame = new JFrame("Operator Dashboard");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 400);
        frame.setLayout(new BorderLayout());

        // Pannello per lo stato del container
        JPanel statusPanel = new JPanel();
        statusPanel.setLayout(new GridLayout(3, 2, 10, 10));
        statusPanel.setBorder(BorderFactory.createTitledBorder("Container Status"));

        // Etichette e valori di stato
        JLabel wasteLevelLabel = new JLabel("Filling Percentage:");
        JLabel wasteLevelValue = new JLabel("0%");

        JLabel temperatureLabel = new JLabel("Temperature:");
        JLabel temperatureValue = new JLabel("22°C");

        JLabel statusLabel = new JLabel("Status:");
        JLabel statusValue = new JLabel("Available");

        // Aggiungo le etichette al pannello di stato
        statusPanel.add(wasteLevelLabel);
        statusPanel.add(wasteLevelValue);
        statusPanel.add(temperatureLabel);
        statusPanel.add(temperatureValue);
        statusPanel.add(statusLabel);
        statusPanel.add(statusValue);
        
        // Pannello per i pulsanti
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new GridLayout(1, 2, 10, 10));
        buttonPanel.setBorder(BorderFactory.createTitledBorder("Operator actions"));
        
        // Pulsante per svuotare il container
        JButton emptyButton = new JButton("EMPTY THE CONTAINER");
        emptyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Simulo lo svuotamento del contenitore
                JOptionPane.showMessageDialog(frame, "The container has been emptied!", "Action completed", JOptionPane.INFORMATION_MESSAGE);
                wasteLevelValue.setText("0%");
                statusValue.setText("Available");
            }
        });
        
        // Pulsante per ripristinare il container
        JButton restoreButton = new JButton("RESTORE");
        restoreButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Simula il ripristino
                JOptionPane.showMessageDialog(frame, "The container has been restored!", "Action completed", JOptionPane.INFORMATION_MESSAGE);
                statusValue.setText("Available");
            }
        });
        
        // Aggiungo i pulsanti al pannello
        buttonPanel.add(emptyButton);
        buttonPanel.add(restoreButton);
        
        // Aggiungo i pannelli alla finestra principale
        frame.add(statusPanel, BorderLayout.CENTER);
        frame.add(buttonPanel, BorderLayout.SOUTH);
        
        // Rendo la finestra visibile
        frame.setVisible(true);
    }
}
