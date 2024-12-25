void Bus::editStop(Node* stop) {
    cout << "Editing stop: " << stop->stop << "\n";
    cout << "Enter new stop name: ";
    cin.ignore();  // To clear any leftover newline characters
    getline(cin, stop->stop);

    cout << "Enter new destination: ";
    getline(cin, stop->destination);

    cout << "Enter new distance (km): ";
    cin >> stop->distance;

    cout << "Enter new time (mins): ";
    cin >> stop->time;

    cout << "Stop updated successfully!\n";

    // After updating the stop, save the changes to the file

    // Open the file to overwrite the bus schedule
    ofstream busScheduleOut("bus_schedule.txt");
    if (!busScheduleOut.is_open()) {
        cerr << "Error: Unable to open bus schedule file for writing.\n";
        return;
    }

    // Write the updated bus data and stops to the file
    for (int i = 0; i < p; i++) {
        busScheduleOut << bus[i].busn << endl;  // Bus number
        busScheduleOut << bus[i].driver << endl; // Driver's name
        busScheduleOut << bus[i].arrival << endl;  // Arrival time
        busScheduleOut << bus[i].depart << endl;  // Departure time

        // Write stops for the bus
        Node* temp = bus[i].head;
        while (temp != nullptr) {
            busScheduleOut << temp->stop << endl;
            busScheduleOut << temp->destination << endl;
            busScheduleOut << temp->distance << endl;
            busScheduleOut << temp->time << endl;
            temp = temp->next;
        }
    }

    busScheduleOut.close();  // Close the file after writing
}

void Bus::removeStop(Node*& head, int stopNumber) {
    if (head == NULL) {
        cout << "No stops to remove.\n";
        return;
    }

    Node* temp = head;

    // If the stop to be removed is the first node
    if (stopNumber == 1) {
        head = temp->next; // Move the head to the next stop
        delete temp;
        cout << "Stop removed successfully!\n";
        // After removing the stop, update the file
        updateBusScheduleToFile();  // File update handled
        return;
    }

    // Find the stop to be removed
    for (int i = 1; temp != NULL && i < stopNumber - 1; i++) {
        temp = temp->next;
    }

    // If stopNumber is greater than the number of stops
    if (temp == nullptr || temp->next == NULL) {
        cout << "Invalid stop number!\n";
        return;
    }

    // Node temp->next is the stop to be deleted
    Node* next = temp->next->next;
    delete temp->next;  // Free memory
    temp->next = next;  // Unlink the deleted stop

    cout << "Stop removed successfully!\n";

    // After removing the stop, update the file
    updateBusScheduleToFile();  // File update handled
}