#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

enum VehicleType { CAR, MOTORCYCLE, TRUCK };

class Vehicle {
private:
    VehicleType type;
    string licensePlate;

public:
    Vehicle(VehicleType type, string licensePlate) : type(type), licensePlate(licensePlate) {}

    VehicleType getType() const { return type; }
    string getLicensePlate() const { return licensePlate; }
};

class ParkingSpot {
private:
    int row;
    int column;
    bool _isAvailable;

public:
    ParkingSpot() : row(0), column(0), _isAvailable(true) {}
    ParkingSpot(int row, int column) : row(row), column(column), _isAvailable(true) {}

    int getRow() const { return row; }
    int getColumn() const { return column; }
    bool isAvailable() const { return _isAvailable; }
    void setAvailable(bool isAvailable) { _isAvailable = isAvailable; }
};

class ParkingLot {
private:
    vector<vector<ParkingSpot>> parkingSpots;
    unordered_map<string, ParkingSpot> parkedVehicles;

public:
    ParkingLot(int rows, int columns) {
        parkingSpots.resize(rows, vector<ParkingSpot>(columns));
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                parkingSpots[row][column] = ParkingSpot(row, column);
            }
        }
    }

    bool parkVehicle(Vehicle vehicle) {
        for (int row = 0; row < parkingSpots.size(); ++row) {
            for (int column = 0; column < parkingSpots[0].size(); ++column) {
                if (parkingSpots[row][column].isAvailable() && canParkVehicle(vehicle, parkingSpots[row][column])) {
                    parkingSpots[row][column].setAvailable(false);
                    parkedVehicles[vehicle.getLicensePlate()] = parkingSpots[row][column];
                    return true;
                }
            }
        }

        return false;
    }

    bool unparkVehicle(string licensePlate) {
        if (parkedVehicles.find(licensePlate) == parkedVehicles.end()) {
            return false;
        }

        ParkingSpot spot = parkedVehicles[licensePlate];
        spot.setAvailable(true);
        parkedVehicles.erase(licensePlate);
        return true;
    }

    int checkAvailability() {
        int availableSpots = 0;
        for (int row = 0; row < parkingSpots.size(); ++row) {
            for (int column = 0; column < parkingSpots[0].size(); ++column) {
                if (parkingSpots[row][column].isAvailable()) {
                    availableSpots++;
                }
            }
        }

        return availableSpots;
    }

    void printParkingLot() {
        for (int row = 0; row < parkingSpots.size(); ++row) {
            for (int column = 0; column < parkingSpots[0].size(); ++column) {
                if (parkingSpots[row][column].isAvailable()) {
                    cout << "A";
                } else {
                    cout << "O";
                }
            }
            cout << endl;
        }
    }

    bool canParkVehicle(Vehicle vehicle, ParkingSpot spot) {
        if (vehicle.getType() == MOTORCYCLE) {
            return true;
        } else if (vehicle.getType() == CAR) {
            return true;
        } else if (vehicle.getType() == TRUCK) {
            // Check if the spot is large enough for a truck
            int row = spot.getRow();
            int column = spot.getColumn();

            // Check if there are enough adjacent available spots for a truck
            int truckSize = 2; // Assuming a truck occupies 2 consecutive spots
            if (column + truckSize <= parkingSpots[0].size()) {
                for (int i = 0; i < truckSize; ++i) {
                    if (!parkingSpots[row][column + i].isAvailable()) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};

int main() {
    ParkingLot parkingLot(3, 5);

    Vehicle car(CAR, "ABC123");
    Vehicle motorcycle(MOTORCYCLE, "DEF456");
    Vehicle truck(TRUCK, "GHI789");

    parkingLot.parkVehicle(car);
    parkingLot.parkVehicle(motorcycle);

    cout << "Available spots: " << parkingLot.checkAvailability() << endl;
    parkingLot.printParkingLot();

    parkingLot.unparkVehicle("ABC123");
    parkingLot.unparkVehicle("DEF456");

    cout << "\nAvailable spots: " << parkingLot.checkAvailability() << endl;
    parkingLot.printParkingLot();

    return 0;
}
