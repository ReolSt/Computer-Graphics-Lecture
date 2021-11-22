if not exist "$(SolutionDir)Debug\Shader\" mkdir "$(SolutionDir)Debug\Shader\"
if not exist "$(ProjectDir)Shader\" mkdir "$(ProjectDir)Shader\"
xcopy "$(SolutionDir)GL\Shader\*" "$(SolutionDir)Debug\Shader\" /Y
xcopy "$(SolutionDir)GL\Shader\*" "$(ProjectDir)Shader\" /Y
