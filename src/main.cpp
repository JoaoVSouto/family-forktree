#include <unistd.h>

#include <iostream>

const std::string BORN_COLOR_ACCENT("\033[1m\033[96m");
const std::string DEATH_COLOR_ACCENT("\033[1m\033[95m");
const std::string WARN_COLOR_ACCENT("\033[1m\033[93m");
const std::string SUB_WARN_COLOR_ACCENT("\033[1;37m");
const std::string RESET_ACCENT("\033[0m");

std::string get_time() {
  const int BUFFER_SIZE = 10;

  time_t rawtime;
  struct tm* info;
  char buffer[BUFFER_SIZE];

  time(&rawtime);

  info = localtime(&rawtime);

  strftime(buffer, BUFFER_SIZE, "%I:%M:%S", info);

  std::string str(buffer, buffer + BUFFER_SIZE);

  return str;
}

void print_born_announcement(std::string person, std::string born_date) {
  std::cout << BORN_COLOR_ACCENT << person << " nasceu em: " << born_date
            << RESET_ACCENT << "\n"
            << std::endl;
}

void print_death_announcement(std::string person, int age,
                              std::string born_date, std::string death_date) {
  std::cout << WARN_COLOR_ACCENT
            << "Morre o " << person << " com " << age << " anos"
            << RESET_ACCENT << std::endl;
  std::cout << SUB_WARN_COLOR_ACCENT << "✝️ Nascimento: " << born_date
            << RESET_ACCENT << std::endl;
  std::cout << DEATH_COLOR_ACCENT << "💀 Morte:      " << death_date
            << RESET_ACCENT << "\n"
            << std::endl;
}

void print_error(std::string msg) {
  std::cout << DEATH_COLOR_ACCENT << "Erro: " << msg
            << RESET_ACCENT << std::endl;
}

int main() {
  pid_t filho1, filho2, neto1, neto2;

  std::string pai_nasc = get_time();
  print_born_announcement("Pai", pai_nasc);

  sleep(14);  // pai tá com 14 anos
  std::string filho1_nasc = get_time();
  print_born_announcement("Filho #1", filho1_nasc);
  filho1 = fork();

  if (filho1 < 0) {
    print_error("não foi possível criar o Filho #1");
    return 1;
  }

  if (filho1 == 0) {
    sleep(12);  // pai tá com 26 anos - filho1 tá com 12 anos
    std::string neto1_nasc = get_time();
    print_born_announcement("Neto #1", neto1_nasc);
    neto1 = fork();

    if (neto1 < 0) {
      print_error("não foi possível criar o Neto #1");
      return 1;
    }

    if (neto1 == 0) {
      sleep(12);  // neto1 tá com 12 anos

      std::string neto1_morte = get_time();
      print_death_announcement("Neto #1", 12, neto1_nasc, neto1_morte);

      exit(0);
    } else {
      sleep(18);  // filho1 tá com 30 anos

      std::string filho1_morte = get_time();
      print_death_announcement("Filho #1", 30, filho1_nasc, filho1_morte);

      exit(0);
    }
  } else {
    sleep(2);  // pai tá com 16 anos
    std::string filho2_nasc = get_time();
    print_born_announcement("Filho #2", filho2_nasc);
    filho2 = fork();

    if (filho2 < 0) {
      print_error("não foi possível criar o Filho #2");
      return 1;
    }

    if (filho2 == 0) {
      sleep(14);  // pai tá com 30 anos - filho2 tá com 14 anos
      std::string neto2_nasc = get_time();
      print_born_announcement("Neto #2", neto2_nasc);
      neto2 = fork();

      if (neto2 < 0) {
        print_error("não foi possível criar o Neto #2");
        return 1;
      }

      if (neto2 == 0) {
        sleep(18);  // neto2 tá com 18 anos

        std::string neto2_morte = get_time();
        print_death_announcement("Neto #2", 18, neto2_nasc, neto2_morte);

        exit(0);
      } else {
        sleep(16);  // filho2 morre com 30 anos

        std::string filho2_morte = get_time();
        print_death_announcement("Filho #2", 30, filho2_nasc, filho2_morte);

        exit(0);
      }
    } else {
      sleep(44);  // pai tá com 60 anos

      std::string pai_morte = get_time();
      print_death_announcement("Pai", 60, pai_nasc, pai_morte);
    }
  }

  return 0;
}
