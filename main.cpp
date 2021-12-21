#include "view/View.h"

View initView() {
    Game game = Game();
    Controller controller = Controller(game);
    return View(controller);
}

int main(int, char **) {
    View view = initView();
    view.loop();
    return 0;
}
