#ifndef GAMEPIECE_H
#define GAMEPIECE_H
#include <QColor>
#include <QGraphicsItem>
class gamepiece : public QGraphicsTextItem {

    Q_OBJECT

public:
    gamepiece(std::string s, int x, int y){
        type = s;
        x_ = x;
        y_ = y;
    };
    std::string get_s(){ return type; }
    void set_x(int x){ x_ = x; }
    void set_y(int y){y_ = y; }
    void set_image(QString s){
        image.load(s);
    }
    QImage get_image(){ return image; }
signals:

protected:



private:
    std::string type;
    int x_;
    int y_;
    static const int width_ = 20;
    QImage image;

};

#endif // GAMEPIECE_H
