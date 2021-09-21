DoubleSpiralCreator가 마우스 입력을  받아
DoubleSpiral 오브젝트를 생성합니다.
DoubleSpiral은 Update 때마다 Next를 호출합니다. 
호출 시마다 mesh에 다음 point를 추가함으로써 애니메이션을 구현합니다.

Next 함수는 precision 파라미터를 받는데, 이는 그리는 점 개수가 몇개인지
나타냅니다. precision이 200이 넘어가면 거의 곡선처럼 보입니다.
마우스 휠로 precision을 조정할 수 있습니다. 50 이하로는 내려가지 않으며
precision에 따른 애니메이션 속도 보정이 있긴 하지만
100000이 넘어가면 그리는 속도가 눈에 띄게 느립니다.
(렉이 아님, 그리는 방식 때문)
또 마우스 휠로 precision 변경시 콘솔 창에 현재 값이 출력됩니다.
변경된 값은 새 곡선을 그릴 때 적용됩니다.

double spiral은 time step으로 결정되는 radian 값에 size multiplier를 곱하여
그려집니다. 의사 코드로 나타내면
time step이 0보다 작을 때 (-cos(radian) * current_size, sin(radian) * current_size)
time step이 0보다 클 때 (-cos(radian) * current_size, sin(radian) * current_size)

배경색은 클릭시마다 랜덤으로 바뀌고 그려지는 double spiral의 색은
배경색의 반전색입니다.