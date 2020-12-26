#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// ���������
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// callback-�������
// glfw: ������ ���, ����� ���������� ������� ���� (������������� ��� ���������� ��������), 
// ���������� ������ callback-�������
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ����������, ��� ���� ��������� ������������� ����� �������� ���� 
    // �������� ��������, ��� ������ � ������ ����� ����������� ������, ��� ������� �� Retina-��������
    glViewport(0, 0, width, height);
}

// ��������� ���� ������� �����: ������ GLFW � �������/���������� ������ �� ���������� � 
// ������ ����� � ��������������� ��������� ������ �������
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // ������� Esc
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ���������������� ������� ����, ���� ����������� macOS
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // �������� ������� window, �������������� ���� ����������
    GLFWwindow* window = glfwCreateWindow(800, 600, " OpenGL test", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // �������� GLFW ������� �������� ������ ���� �������� ���������� � ������� ������.
        /* ����� ������������ �������� ������� ����, ������ ���� �������������� � ������ �������
    ���� ���������.��� ����� ���������� ���������� callback - �������
    (��� ��� �������� ��������� ������), ������� ���������� ��� ������ ��������� ������� ����. */

    /* ��� ����, ����� �������� GLFW, ��� �� ����� �������� ������� framebuffer_size_callback()
    ������ ���, ����� ���������� ��������� �������� ���� �� ����� ������� ����������� ���� �����
    ���������� ������� framebuffer_size_callback(), ������� ����������� ������� ����������� ����.*/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /*GLAD ��������� ����������� �� OpenGL - �������, ������� �� ������ ������� ���������������� GLAD, 
        � ������ ����� ����� ����� ������������ OpenGL - ���������*/
    /* � �������� ��������� �� ������� GLAD - �������, ������� ��������� ������ ���������� �� OpenGL -
    �������(������� ����� ���������� � ����������� �� ������������ ���� ��)*/
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glViewport(0, 0, 800, 600); //  ���� ���������

    // ���� ����������
    // ������� glfwWindowShouldClose() ���������, �������� �� �� GLFW ������� ����������.

    // glfwPollEvents() ������ �� ���, ������������ �� �����-���� ������� (��������, 
    // ���� � ���������� ��� ����������� �����), ��������� ��������� ���� � �������� ��������������� 
    // ������� (������� �� ����� ���������������� � ������� callback-�������)

    // ������� glfwSwapBuffers() ������ ������� �������� ����� (������� 2D-�����, 
    // ���������� �������� ����� ��� ������� ������� � ���� GLFW), ������� ������������ 
    // ��� ���������� �� ����� ������ �������� ����������, � ������� ��� �� �����.

    // ����� (��� ���� ����� ���������� �������� � ����� ����������
    while (!glfwWindowShouldClose(window))
    {
        // ��������� �����
        processInput(window);

        // ���������� ����������
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: ����� ���������� front- � back- �������. 
        // ������������ ������� �����/������� (���� �� ������/�������� ������, ��������� ������ ���� � �.�.)

        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    // �������/�������� ���� ���������� ��� GLFW ��������
    glfwTerminate();

    return 0;
}