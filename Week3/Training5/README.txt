이등변삼각형을 그리기 위해
구현한 라이브러리의 GLObject를 상속하여
IsoscelesTriangleObject를 만들었습니다.

GLObject에는 shader program을 할당할 수 있고,
여러 GLMesh를 포함할 수 있습니다.
또 Update 함수로 매 프레임마다 처리해야 하는 로직을
처리하고, Render 함수로 렌더링합니다.

glPolygonMode로 도형을 면으로 그릴지 선으로 그릴지 정합니다.
size_multiplier가 1.5보다 커지면 size_multiplier_direction이 반전되어
작아지고, size_multiplier가 0.5보다 작아지면 커지는 방향으로 바뀝니다.
size_multiplier는 마우스 클릭시마다 size_multiplier_direcion 만큼 변합니다.