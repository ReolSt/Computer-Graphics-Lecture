실습 4문제 전체에 대한 README입니다.

솔루션 파일(Week2Training.sln)을 열면
Training1, Training2, Training3, Training4 프로젝트가 있습니다.
각각을 시작 프로젝트로 설정하고 빌드하면 실행할 수 있습니다.

코드 재사용을 위해 GL이 접두사로 붙은
작은 라이브러리를 작성하였습니다.
핵심 로직이 들어있는 부분은 이벤트 핸들러를
처리하는 GLMain 클래스입니다.
GLMain 클래스는 템플릿 클래스인 Singleton을 상속하여
한번에 하나의 인스턴스만 존재할 수 있도록 했습니다.
멤버 함수로 On 접두사를 가진 메소드들이 존재하며,
이들은 인스턴스화 시에 자동적으로 glut****Func 함수를 통해
콜백으로 등록됩니다.

SetTimeout, SetInterval, ClearInterval은 편리하게 타이머 콜백을
등록할 수 있도록 만드는 glutTimerFunc의 wrapper입니다.
int값인 id를 이용해 콜백들을 관리할 수 있습니다.
이 wrapper는 glut의 타이머 콜백과는 달리
함수 객체나 람다를 타이머 콜백 함수로 등록할 수 있습니다.
이 기능은 내부적인 함수인 __GLMainIntervalCallbackRunner를
통해 제공됩니다.

각 실습에서는 GLMain 클래스를 상속하여 요구사항을
구현합니다.

그 이외에 구현에서의 편리함과 재사용성을 위해
GLColor, GLVector, GLWindow 등의 클래스를 만들었으며,
GLHelpers에서 이들을 편리하게 opengl함수로 전달할 수 있도록
wrapper를 제공합니다.