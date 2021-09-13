GLColor 클래스를 작성하여 GLColor를 glColor 계열의 함수에
집어넣는 wrapper로 색 변경을 구현했습니다.

r, g, b, w, k는 각각 빨간색, 녹색, 파란색, 흰색, 검은색으로
배경색을 바꾸며, t를 입력하면 람다 함수 객체가 interval callback
으로 등록되어 0.5초마다 배경색을 랜덤하게 변경합니다.
이후 s를 입력하면 ClearInterval 함수로 콜백 함수 실행을 중단합니다.
