Таки чтобы повернуть грань куба, берёшь такой, и дёргаешь его за rotate(Direction).
Direction можно создать хоть от строки, хоть от грани с видом поворота.
А еще можно забить на Direction и крутить кубик прямо так!
Вот, таки, пример:
    Cube cube;
    Direction dir1("F'");
    Direction dir2(LEFT, HALF_TURN);
    cube.rotate(dir1);
    cube.rotate(dir2);
    cube.rotate("L");
    cube.rotate(FRONT, COUNTER_CLOCKWISE);


Таки чтобы читать из куба есть getCubie. Хочешь узнать что творится между двумя гранями, ну так
передай туда две грани. Хочешь узнать, что творится между тремя гранями, ну так передай туда
три грани. Госпади, как же это сложна писос (нет). В ответ получаешь тьюпл в котором хранятся
цвета в соответсвующем граням порядке. Если ты вдруг решишь спросить что-нибудь про грани,
которые не являются соседями, то всё грохнется со страшной силой.

Ты не поверишь, но теперь можно вращать даже центры. Возможно, оно даже работает.
    Cube cube;
    cube.rotate("E");
    cube.rotate("M2");
    cube.rotate("S'");

Алсо, можно повернуть кубик влево. Для этого есть таки метод повернуть влево:
    Cube cube;
    cube.turnLeft();


Воу воу, я завел алиасы для тьюплов. Cubie из двух PlaneType теперь Duo, а cubie из
трех PlaneType теперь Triple.
Воу воу, я сделал класс Mask и добавил кубу метод fitsMask, который возвращает bool.
В класс Mask можно задавать цвета cubieков парами, а можно сразу целым скопом:
    Mask m;
    m.setCubie(Duo{plane1, plane2}, Duo{plane_1, plane_2}); // задает, что между гранями plane1 и plane2
                                                            // должен быть plane_1, plane_2
    m.setCubie(Triple{plane1, plane2, plane3}, Triple{plane1, plane2, plane3}); // тож самое, только для угловых cubieков

    m.setCubies(                                                            // тож самое, только сразу целым скопом
        QVector<Duo>{Duo{BACK, UP},    Duo{UP, LEFT}, Duo{RIGHT, DOWN}},    // вместо QVector может быть любой контейнер
        QVector<Duo>{Duo{LEFT, FRONT}, Duo{RIGHT, UP}, Duo{LEFT, UP}}       // вместо Duo есессна может быть Triple
    );

