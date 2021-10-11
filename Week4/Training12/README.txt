RectangleCreator가 랜덤으로 사각형을 100개 생성하고,
eraser에 해당하는 사각형을 MouseDown시 visible=true,
MouseUp시 visible=false 해서 드래그 시에만 보이게 하고,
AABB로 eraser와 각 사각형이 충돌하는지 파악하여 충돌하면
사각형을 지웁니다.