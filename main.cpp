#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <unistd.h>

using namespace std;

int main() {
  const time_t INITIAL_TIME = time(nullptr);
  const tm INITIAL_CALENDAR_TIME = *localtime(addressof(INITIAL_TIME));
  int first_response, saving_option_response;
  string subject, initial_hours, initial_minutes, random_letter_to_show_menu;

  while (true) {
    system("cls");
    cout << "What do you want to do?\n(1) New session  (2) Show sessions  (3) "
            "Quit  => ";
    cin >> first_response;

    if (first_response == 1) {
      cout << "What subject do you have to study?  => ";
      cin >> subject;
      system("cls");
      cout << subject << " session is started!\n";
      initial_hours = INITIAL_CALENDAR_TIME.tm_hour;
      initial_minutes = INITIAL_CALENDAR_TIME.tm_min;
      cout << "WHEN YOUR STUDY SESSION IS FINISHED, press a random letter and "
              "then press enter to show the menu\n";
      cin >> random_letter_to_show_menu;
      system("cls");
      cout << "What do you want to do now?\n(1) Save and quit  (2) Quit "
              "without save  => ";
      cin >> saving_option_response;
      if (saving_option_response == 1) {
        const time_t FINAL_TIME = time(nullptr);
        const tm FINAL_CALENDAR_TIME = *localtime(addressof(FINAL_TIME));

        int total_hours =
            FINAL_CALENDAR_TIME.tm_hour - INITIAL_CALENDAR_TIME.tm_hour;
        int total_minutes =
            FINAL_CALENDAR_TIME.tm_min - INITIAL_CALENDAR_TIME.tm_min;

        if (total_minutes < 0) {
          total_minutes = 60 - total_minutes;
          total_hours--;
        }

        ofstream file("sessions.txt", ios::app);
        file << endl
             << INITIAL_CALENDAR_TIME.tm_year + 1900 << "/"
             << INITIAL_CALENDAR_TIME.tm_mon + 1 << "/"
             << INITIAL_CALENDAR_TIME.tm_wday << "\nSubject: " << subject
             << "\nDuration time: " << total_hours << "h" << ":"
             << total_minutes << "m\n";
        file.close();
      } else {
        break;
      }
    } else if (first_response == 2) {
      system("type sessions.txt");
      cout << "After 10 seconds, you will be redirect to the main menu\n";
      sleep(10);
    } else if (first_response == 3) {
      break;
    } else {
      cout << "This isn't an optionm try again." << endl;
    }
  }
}
