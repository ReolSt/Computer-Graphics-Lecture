Week3 솔루션 내에
GL, Training5, Training6, ... , Training10
총 7개의 프로젝트가 있습니다.
GL을 제외한 프로젝트들이 각 실습에 대한 구현입니다.
GL 폴더에는 과제 구현을 위한 작은 엔진 및 라이브러리가 들어있습니다.
(기존에 만들어놓은것 아님, 어디서 가져온거 아님)

기본적으로 GLGameObject를 상속받은 클래스들을 정의해
GLScene의 root object에 자식으로 추가하여 게임 혹은 기능을 구현합니다.
GLMain에서는 기본 환경과 glut 이벤트 핸들러를 관리하며, GLScene을 통해
GLGameObject에 외부 환경의 이벤트(키보드, 마우스 등)를 전달합니다.