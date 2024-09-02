# Sensors - Programmazione ad Oggetti

Progetto realizzato da **Marco Cola** per il corso di **Programmazione ad Oggetti** del corso di Laurea in Informatica presso l'Università di Padova nell'a.a. 2023/2024.

## Descrizione del Progetto

L'obiettivo del progetto è sviluppare una simulazione di sensori utilizzando il linguaggio di programmazione **C++** e il framework **Qt** per creare un'interfaccia grafica utente (GUI). La simulazione permette agli utenti finali di:

- Definire nuovi sensori (di temperatura, umidità e polveri sottili).
- Modificare o cancellare sensori esistenti.
- Avviare e monitorare una simulazione dei sensori definiti.
- Consentire la persistenza dei dati (il progetto permette di salvare i sensori creati in un file .txt)
  
  Per altre informazioni leggere la ![relazione](./doc/Relazione_Sensors.pdf)


## Esempio GUI
![Screenshot from 2024-09-01 11-41-45](https://github.com/user-attachments/assets/4519fa11-8dd1-4ec1-a50c-20b2298a660e)


## Requisiti

Assicurati di avere i seguenti strumenti installati sul tuo sistema per compilare ed eseguire il progetto:

- **C++ Compiler** 
- **Qt Framework** (versione 5.15 o superiore)
  

## Istruzioni per l'Installazione

1. **Clona il repository**:
   
   ```c
   git clone https://github.com/cola-marco/Sensors.git
   cd Sensors


2. **Compila il progetto con qt**:
   
    ```c
    qmake6
    make
3. **Esegui l'applicazione**:
   
   ```c
   ./Sensors  
