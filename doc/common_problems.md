# 
1. Remember to clear `GL_DEPTH_BUFFER_BIT`, when enable `glEnable(GL_DEPTH_TEST)`
    ```
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    ```