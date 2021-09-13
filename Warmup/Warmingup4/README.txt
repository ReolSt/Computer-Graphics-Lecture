직선, 직사각형에 대해 각각 Line, Rectangle이라는 구조체를 만들었습니다.

STL random 라이브러리로 랜덤하게 초기화하였습니다.

직선, 직사각형 이동은 move_line, move_rectangle 함수를 사용하는데,
이동했을때 좌표가 범위를 벗어나는지 체크하여 결과를 리턴합니다.

충돌 체크시에 사용하는 함수는 is_colliding인데,
랜덤하게 생성한 직사각형의 두 좌표를 각각 lefttop, bottomright라 정의하여
left, right, bottom, top 값을 구한 후
해당 범위에 직선의 정점 값 중 하나라도 범위에 포함되어 있는지 확인합니다.