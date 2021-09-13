마우스 드래그 시 시작점에 상관 없이 delta 값을 구하여
dx, dy만큼 사각형을 이동시킵니다.
이때 ScreenToWorldPoint 함수로 윈도우 좌표에서
opengl 좌표로 변환합니다.

또 사각형을 클릭하면 색을 랜덤하게 변경합니다.

GLVector 형태의 값을 glRectf로 편리하게 전달하기 위해
wrapper 함수를 사용하였습니다.