#include "window/eventing/event_manager.hpp"
#include "window/eventing/input_events.hpp"
#include "window/eventing/window_events.hpp"
// #include "window/glfw.hpp"

#include <GLFW/glfw3.h>

namespace Window::Eventing
{
    EventManager::EventManager(GLFWwindow* window)
    {
        glfwSetWindowUserPointer(window, this);

        auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            EventManager* current = static_cast<EventManager*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (action == GLFW_PRESS)
                {
                    Eventing::KeyPressEvent pressEvent(static_cast<Inputs::EKey>(key));
                    current->invoke(pressEvent);
                }

                if (action == GLFW_RELEASE)
                {
                    Eventing::KeyReleaseEvent releaseEvent(static_cast<Inputs::EKey>(key));
                    current->invoke(releaseEvent);
                }
            }
        };

        glfwSetKeyCallback(window, keyCallback);

        auto mouseCallback = [](GLFWwindow* window, int button, int action, int mods)
        {
            EventManager* current = static_cast<EventManager*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (action == GLFW_PRESS)
                {
                    Eventing::MousePressEvent pressEvent(static_cast<Inputs::EMouseButton>(button));
                    current->invoke(pressEvent);
                }
                
                if (action == GLFW_RELEASE)
                {
                    Eventing::MouseReleaseEvent releaseEvent(static_cast<Inputs::EMouseButton>(button));
                    current->invoke(releaseEvent);
                }
            }
        };

        glfwSetMouseButtonCallback(window, mouseCallback);

        auto cursorMoveCallback = [](GLFWwindow* window, double x, double y)
        {
            EventManager* current = static_cast<EventManager*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::MouseMoveEvent moveEvent(x, y);
                current->invoke(moveEvent);
            }
        };

        glfwSetCursorPosCallback(window, cursorMoveCallback);

        auto scrollCallback = [](GLFWwindow* window, double offsetX, double offsetY)
        {
            EventManager* current = static_cast<EventManager*>(glfwGetWindowUserPointer(window));
            
            if (current)
            {
                Eventing::MouseScrollEvent scrollEvent(offsetX, offsetY);
                current->invoke(scrollEvent);
            }
        };

        glfwSetScrollCallback(window, scrollCallback);

        auto resizeCallback = [](GLFWwindow* window, int width, int height)
        {
            EventManager* current = static_cast<EventManager*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::WindowResizeEvent resizeEvent(width, height);
                current->invoke(resizeEvent);
            }
        };

        glfwSetWindowSizeCallback(window, resizeCallback);

        auto framebufferResizeCallback = [](GLFWwindow* window, int width, int height)
        {
            EventManager* current = static_cast<EventManager*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::FramebufferResizeEvent resizeEvent(width, height);
                current->invoke(resizeEvent);
            }
        };

        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

        auto moveCallback = [](GLFWwindow* window, int x, int y)
        {
            EventManager* current = static_cast<EventManager*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::WindowMoveEvent moveEvent(x, y);
                current->invoke(moveEvent);
            }
        };

        glfwSetWindowPosCallback(window, moveCallback);

        auto iconifyCallback = [](GLFWwindow* window, int iconified)
        {
            EventManager* current = static_cast<EventManager*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (iconified == GLFW_TRUE)
                {
                    Eventing::WindowMinimizeEvent minEvent;
                    current->invoke(minEvent);
                }

                if (iconified == GLFW_FALSE)
                {
                    Eventing::WindowMaximizeEvent maxEvent;
                    current->invoke(maxEvent);
                }
            }
        };

        glfwSetWindowIconifyCallback(window, iconifyCallback);

        auto focusCallback = [](GLFWwindow* window, int focused)
        {
            EventManager* current = static_cast<EventManager*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (focused == GLFW_TRUE)
                {
                    Eventing::WindowGainFocusEvent gainEvent;
                    current->invoke(gainEvent);
                }

                if (focused == GLFW_FALSE)
                {
                    Eventing::WindowLostFocusEvent lostEvent;
                    current->invoke(lostEvent);
                }
            }
        };

        glfwSetWindowFocusCallback(window, focusCallback);

        auto closeCallback = [](GLFWwindow* window)
        {
            EventManager* current = static_cast<EventManager*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::WindowCloseEvent closeEvent;
                current->invoke(closeEvent);
            }
        };

        glfwSetWindowCloseCallback(window, closeCallback);

        glfwSetWindowUserPointer(window, nullptr);
    }

    EventManager::~EventManager()
    {
        removeAllListeners();
    }
}
