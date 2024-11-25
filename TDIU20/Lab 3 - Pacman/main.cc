#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ghost.h"
using namespace std;

/*
  Ledning och Tips:
  
  - Modifiera stukturen till en header-fil och en implementationsfil
  - Utöka 'run()' och 'draw_map()' med övrig funktionalitet.
  - Lägg alla spöken i en lämplig behållare som en datamedlem.
  - Bryt ut stora kodblock till egna funktioner.
  - Använd hjälpfunktioner för att undvika duplicering av kod.
  - Tänk på att varje funktion inte borde vara längre än 25 rader.
*/



class Ghost_Tester {
public:
  enum GhostMode { Scatter, Chase };
  int current_mode{0};
  
  Ghost_Tester() : pacman(), ghosts() {
    ghosts.push_back(
		     new Blinky(pacman, Point{2, 6}, Point{WIDTH - 1, HEIGHT - 1}));
    ghosts.push_back(new Pinky(pacman, Point{4, 5}, Point{0, HEIGHT - 1}));
    ghosts.push_back(new Clyde(pacman, Point{6, 3}, Point{0, 0}, 6));
    ghosts.push_back(
		     new Inky(pacman, Point{}, Point{WIDTH - 1, 0}, *ghosts[0]));
    
    set_mode(GhostMode::Chase);
  }
  
  ~Ghost_Tester() {
    for (auto ghost : ghosts) {
      delete ghost;
        }
  }
  
  void randomize_positions() {
    pacman.set_position({rand() % WIDTH, rand() % HEIGHT});
    for (auto& ghost : ghosts) {
      ghost->set_position({rand() % WIDTH, rand() % HEIGHT});
    }
  }
  
  void set_mode(GhostMode mode) { current_mode = mode; }
  
  void run() {
    while (true) {
      draw_map();
      cout << "> ";
      
      string line{};
      getline(cin, line);
      istringstream iss(line);
      
      string command{};
      iss >> command;
      
      if (command == "quit") {
	break;
      }
      
      handle_command(command, iss);
    }
  }
  
private:
  void handle_command(const string& command, istringstream& iss) {
    if (command == "pos" || command == "dir") {
      set_pacman(command, iss);
    } else if (command == "anger") {
      set_blinky_anger(iss);
    } else if (command == "scatter") {
      set_mode(GhostMode::Scatter);
    } else if (command == "chase") {
      set_mode(GhostMode::Chase);
    } else if (command == "random") {
      randomize_positions();
    } else {
      move_ghost(command, iss);
    }
  }
  
  void set_pacman(const string& command, istringstream& iss) {
    Point n{};
    iss >> n.x >> n.y;
    if (command == "pos") {
      pacman.set_position(n);
    } else {
      pacman.set_direction(n);
    }
  }
  
  void move_ghost(const string& command, istringstream& iss) {
    /* Hämtar alla färger från ghost containern
     * och lägger in dem i en färg lista
     */
    vector<string> colorList;
    for (auto& ghost : ghosts) {
      colorList.push_back(ghost->get_color());
    }
    
    /* Kollar om färgen/kommandot
     * finns i färg listan
     */
    bool colorExists{false};
    for (const string& color : colorList) {
      if (color == command) {
	colorExists = true;
	break;
      }
    }
    
    // Returnera om kommandot är ogiltigt
    if (!colorExists) {
      return;
    }
    
    string ghost_color{command};
    Point new_pos{};
    iss >> new_pos.x >> new_pos.y;
    
    for (auto& ghost : ghosts) {
      if (ghost->get_color() == ghost_color) {
	ghost->set_position(new_pos);
	break;
      }
    }
  }
  
  void set_blinky_anger(istringstream& iss) {
    string angry{};
    iss >> angry;
    bool is_angry{false};
    if (angry == "true" || angry == "1") {
      is_angry = true;
    }
    
    for (auto& ghost : ghosts) {
      Blinky* blinkyPtr = dynamic_cast<Blinky*>(ghost);
      if (blinkyPtr != nullptr) {
	blinkyPtr->set_angry(is_angry);
	break;
      }
    }
  }
  
  Point get_ghost_goal(Ghost* ghost) {
    Point goal{};
    
    if (current_mode == GhostMode::Scatter) {
      goal = ghost->get_scatter_point();
    } else if (current_mode == GhostMode::Chase) {
      goal = ghost->get_chase_point();
    }
    return goal;
  }
  
  /*
    En hjälpfunktion som avgör vilka två tecken som ska ritas ut för en given
    position på spelplanen.
  */
  string to_draw(Point const& curr_pos) {
    string to_draw{"  "};
    
    // Här ska du rita ut spöket baserat på dess current_position
    for (const auto& ghost : ghosts) {
      if (ghost->get_position() == curr_pos) {
	to_draw[0] = toupper(ghost->get_color()[0]);
      }
    }
    
    // Och här ska du rita ut målpositionen baserat på dess target_position
    for (const auto& ghost : ghosts) {
      Point goal = get_ghost_goal(ghost);
      if (goal == curr_pos) {
	to_draw[0] = tolower(ghost->get_color()[0]);
      }
    }
    
    // Se till att pacman positionen ritas ut sist för att pacman ska kunna
    // "överskriva" spöken på samma position
    if (pacman.get_position() == curr_pos) {
      to_draw[1] = '@';
    }
    
    return to_draw;
  }
  
  void draw_map() {
    cout << "+" << setfill('-') << setw(WIDTH * 2) << "-"
	 << "+\n";
    
    for (int y{HEIGHT - 1}; y >= 0; --y) {
      cout << "|";
      for (int x{}; x < WIDTH; ++x) {
	cout << to_draw(Point{x, y});
      }
      cout << "|\n";
    }
    
    cout << "+" << setfill('-') << setw(WIDTH * 2) << "-"
	 << "+" << endl;
  }
  
  Pacman pacman;
  vector<Ghost*> ghosts;
};

int main() {
  Ghost_Tester gt{};
  gt.run();
  return 0;
}
