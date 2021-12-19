//
// Created by antonio on 19. 12. 2021..
//

#ifndef WPIPES_PIPE_H
#define WPIPES_PIPE_H


class Pipe {
    bool openLeft;
    bool openTop;
    bool openRight;
    bool openBottom;
public:
    explicit Pipe(bool first = false);
    Pipe(bool openLeft, bool openTop, bool openRight, bool openBottom);
    Pipe getPipe() const;
    bool getLeft() const;
    bool getRight() const;
    bool getTop() const;
    bool getBottom() const;
    void setBottom();
    void setTop();
    void setRight();
    void setLeft();
    void setPipe(Pipe& pipe);
};


#endif //WPIPES_PIPE_H
