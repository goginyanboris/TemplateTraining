#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Константы
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// callback-функция
// glfw: всякий раз, когда изменяются размеры окна (пользователем или оперионной системой), 
// вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна 
    // Обратите внимание, что ширина и высота будут значительно больше, чем указано на Retina-дисплеях
    glViewport(0, 0, width, height);
}

// Обработка всех событий ввода: запрос GLFW о нажатии/отпускании клавиш на клавиатуре в 
// данном кадре и соответствующая обработка данных событий
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // нажатие Esc
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Раскомментируйте строчку ниже, если используете macOS
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // создание объекта window, представляющий окно приложения
    GLFWwindow* window = glfwCreateWindow(800, 600, " OpenGL test", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // сообщаем GLFW сделать контекст нашего окна основным контекстом в текущем потоке.
        /* когда пользователь изменяет размеры окна, должен быть скорректирован и размер области
    окна просмотра.Для этого необходимо определить callback - функцию
    (или ещё «функцию обратного вызова), которая вызывается при каждом изменении размера окна. */

    /* Для того, чтобы сообщить GLFW, что мы хотим вызывать функцию framebuffer_size_callback()
    всякий раз, когда происходит изменение размеров окна Во время первого отображения окна также
    вызывается функция framebuffer_size_callback(), имеющая аналогичные размеры полученного окна.*/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /*GLAD оперирует указателями на OpenGL - функции, поэтому мы должны сначала инициализировать GLAD, 
        и только после этого можно пользоваться OpenGL - функциями*/
    /* В качестве параметра мы передаём GLAD - функцию, которая загружает адреса указателей на OpenGL -
    функции(которые могут отличаться в зависимости от используемой вами ОС)*/
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glViewport(0, 0, 800, 600); //  окно просмотра

    // цикл рендеринга
    // Булевая glfwWindowShouldClose() проверяет, сообщали ли мы GLFW закрыть приложение.

    // glfwPollEvents() следит за тем, инициируются ли какие-либо события (например, 
    // ввод с клавиатуры или перемещение мышки), обновляет состояние окна и вызывает соответствующие 
    // функции (которые мы можем зарегистрировать с помощью callback-методов)

    // Функция glfwSwapBuffers() меняет местами цветовой буфер (большой 2D-буфер, 
    // содержащий значения цвета для каждого пикселя в окне GLFW), который используется 
    // для рендеринга во время данной итерации рендеринга, и выводит его на экран.

    // фрейм (так чаще всего называется итерация в цикле рендеринга
    while (!glfwWindowShouldClose(window))
    {
        // Обработка ввода
        processInput(window);

        // Выполнение рендеринга
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: обмен содержимым front- и back- буферов. 
        // Отслеживание событий Ввода/Ввывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)

        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    // очистка/удаление всех выделенных для GLFW ресурсов
    glfwTerminate();

    return 0;
}