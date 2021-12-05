if not exist "$(TargetDir)shaders\" mkdir "$(TargetDir)shaders\"
if not exist "$(TargetDir)resources\" mkdir "$(TargetDir)resources\"
if not exist "$(ProjectDir)shaders\" mkdir "$(ProjectDir)shaders\"
if not exist "$(ProjectDir)\resources\" mkdir "$(ProjectDir)\resources\"
copy "$(SolutionDir)GL\shaders\*" "$(TargetDir)shaders\" /Y
copy "$(SolutionDir)GL\shaders\*" "$(ProjectDir)shaders\" /Y
copy "$(SolutionDir)resources\*" "$(TargetDir)resources\" /Y
copy "$(SolutionDir)resources\*" "$(ProjectDir)resources\" /Y