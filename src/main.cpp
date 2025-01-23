#include "M5Cardputer.h"
#include "M5GFX.h"

M5Canvas canvas(&M5Cardputer.Display);
String data = "> ";
String operation = "";
void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextSize(1.5);
    M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(),
                                 M5Cardputer.Display.height() - 28, GREEN);

    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4,
                                 M5Cardputer.Display.width(), 4, GREEN);

    canvas.setTextSize(1.5);
    canvas.createSprite(M5Cardputer.Display.width() - 8,
                        M5Cardputer.Display.height() - 36);
    canvas.setTextScroll(true);
    canvas.println("!h - help");
    canvas.pushSprite(4, 4);
    M5Cardputer.Display.drawString(data, 4, M5Cardputer.Display.height() - 24);
}

void calculate() {
    char buffer[20];  // Buffer for number formatting
    if (operation.indexOf("+") > 0) {
        float a = operation.substring(0, operation.indexOf("+")).toFloat();
        float b = operation.substring(operation.indexOf("+") + 1).toFloat();
        dtostrf(a + b, 0, 10, buffer);
        operation = String(buffer);
        operation.trim();  // Remove leading/trailing spaces
        // Remove trailing zeros after decimal point
        while (operation.endsWith("0")) {
            operation = operation.substring(0, operation.length() - 1);
        }
        if (operation.endsWith(".")) {
            operation = operation.substring(0, operation.length() - 1);
        }
    } else if (operation.indexOf("-") > 0) {
        float a = operation.substring(0, operation.indexOf("-")).toFloat();
        float b = operation.substring(operation.indexOf("-") + 1).toFloat();
        dtostrf(a - b, 0, 10, buffer);
        operation = String(buffer);
        operation.trim();
        while (operation.endsWith("0")) {
            operation = operation.substring(0, operation.length() - 1);
        }
        if (operation.endsWith(".")) {
            operation = operation.substring(0, operation.length() - 1);
        }
    } else if (operation.indexOf("*") > 0) {
        float a = operation.substring(0, operation.indexOf("*")).toFloat();
        float b = operation.substring(operation.indexOf("*") + 1).toFloat();
        dtostrf(a * b, 0, 10, buffer);
        operation = String(buffer);
        operation.trim();
        while (operation.endsWith("0")) {
            operation = operation.substring(0, operation.length() - 1);
        }
        if (operation.endsWith(".")) {
            operation = operation.substring(0, operation.length() - 1);
        }
    } else if (operation.indexOf("/") > 0) {
        float a = operation.substring(0, operation.indexOf("/")).toFloat();
        float b = operation.substring(operation.indexOf("/") + 1).toFloat();
        if (b == 0) {
            operation = "Error: Division by zero";
            return;
        }
        dtostrf(a / b, 0, 10, buffer);
        operation = String(buffer);
        operation.trim();
        while (operation.endsWith("0")) {
            operation = operation.substring(0, operation.length() - 1);
        }
        if (operation.endsWith(".")) {
            operation = operation.substring(0, operation.length() - 1);
        }
    } else if (operation.indexOf("^") > 0) {
        float a = operation.substring(0, operation.indexOf("^")).toFloat();
        float b = operation.substring(operation.indexOf("^") + 1).toFloat();
        if (b < 0) {
            operation = "Not supported for now :(";
            return;
        }
        dtostrf(pow(a, b), 0, 10, buffer);
        operation = String(buffer);
        operation.trim();
        while (operation.endsWith("0")) {
            operation = operation.substring(0, operation.length() - 1);
        }
        if (operation.endsWith(".")) {
            operation = operation.substring(0, operation.length() - 1);
        }
    } else if (operation.indexOf("sqrt(") >= 0) {
        float a = operation.substring(operation.indexOf("sqrt(") + 5).toFloat();
        if (a < 0) {
            operation = "Error: Invalid input for sqrt";
            return;
        }
        dtostrf(sqrt(a), 0, 10, buffer);
        operation = String(buffer);
        operation.trim();
        while (operation.endsWith("0")) {
            operation = operation.substring(0, operation.length() - 1);
        }
        if (operation.endsWith(".")) {
            operation = operation.substring(0, operation.length() - 1);
        }
    } else {
        operation = "Error: Invalid operation";
    }
}

void loop() {
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

            for (auto i : status.word) {
                data += i;
            }

            if (status.del) {
                data.remove(data.length() - 1);
            }

            if (status.enter) {
                data.remove(0, 2);
                operation = data;
                if(operation == "!h"){
                    canvas.println("Simple Calculator alpha 1.0");
                    canvas.println("Commands:");
                    canvas.println("!h - help, !hc - help color");
                    canvas.println("Operations:");
                    canvas.println("a + b   a * b   a ^ b");
                    canvas.println("a - b   a / b   sqrt(a)");
                    canvas.println("pi");
                }
                else if(operation == "!hc"){
                    canvas.println("Colors:");
                    canvas.println("Set by typing text_COLOR or rect_COLOR");
                    canvas.println("BLUE    YELLOW  ORANGE");
                    canvas.println("RED     GREEN   PINK");
                    canvas.println("WHITE   PURPLE");
                }
                else if(operation == "text_PURPLE" || operation == "text_purple" || operation == "TEXT_purple" || operation == "TEXT_PURPLE" || operation == "textpurple" || operation == "TEXTPURPLE"){ 
                    M5Cardputer.Display.setTextColor(TFT_PURPLE);
                } else if(operation == "rect_PURPLE" || operation == "rect_purple" || operation == "RECT_purple" || operation == "RECT_PURPLE" || operation == "rectpurple" || operation == "RECTPURPLE") {
                    M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(),
                             M5Cardputer.Display.height() - 28, PURPLE);
                    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4,
                             M5Cardputer.Display.width(), 4, PURPLE);
                }
                else if(operation == "text_YELLOW" || operation == "text_yellow" || operation == "TEXT_yellow" || operation == "TEXT_YELLOW" || operation == "textyellow" || operation == "TEXTYELLOW") {
                    M5Cardputer.Display.setTextColor(TFT_YELLOW);
                } else if(operation == "rect_YELLOW" || operation == "rect_yellow" || operation == "RECT_yellow" || operation == "RECT_YELLOW" || operation == "rectyellow" || operation == "RECTYELLOW") {
                    M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(),
                             M5Cardputer.Display.height() - 28, YELLOW);
                    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4,
                             M5Cardputer.Display.width(), 4, YELLOW);
                }
                else if(operation == "text_GREEN" || operation == "text_green" || operation == "TEXT_green" || operation == "TEXT_GREEN" || operation == "textgreen" || operation == "TEXTGREEN") {
                    M5Cardputer.Display.setTextColor(TFT_GREEN);
                } else if(operation == "rect_GREEN" || operation == "rect_green" || operation == "RECT_green" || operation == "RECT_GREEN" || operation == "rectgreen" || operation == "RECTGREEN") {
                    M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(),
                             M5Cardputer.Display.height() - 28, GREEN);
                    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4,
                             M5Cardputer.Display.width(), 4, GREEN);
                }
                else if(operation == "text_RED" || operation == "text_red" || operation == "TEXT_red" || operation == "TEXT_RED" || operation == "textred" || operation == "TEXTRED") {
                    M5Cardputer.Display.setTextColor(TFT_RED);
                } else if(operation == "rect_RED" || operation == "rect_red" || operation == "RECT_red" || operation == "RECT_RED" || operation == "rectred" || operation == "RECTRED") {
                    M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(),
                             M5Cardputer.Display.height() - 28, RED);
                    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4,
                             M5Cardputer.Display.width(), 4, RED);
                }
                else if(operation == "text_WHITE" || operation == "text_white" || operation == "TEXT_white" || operation == "TEXT_WHITE" || operation == "textwhite" || operation == "TEXTWHITE") {
                    M5Cardputer.Display.setTextColor(TFT_WHITE);
                } else if(operation == "rect_WHITE" || operation == "rect_white" || operation == "RECT_white" || operation == "RECT_WHITE" || operation == "rectwhite" || operation == "RECTWHITE") {
                    M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(),
                             M5Cardputer.Display.height() - 28, WHITE);
                    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4,
                             M5Cardputer.Display.width(), 4, WHITE);
                }
                else if(operation == "text_ORANGE" || operation == "text_orange" || operation == "TEXT_orange" || operation == "TEXT_ORANGE" || operation == "textorange" || operation == "TEXTORANGE") {
                    M5Cardputer.Display.setTextColor(TFT_ORANGE);
                } else if(operation == "rect_ORANGE" || operation == "rect_orange" || operation == "RECT_orange" || operation == "RECT_ORANGE" || operation == "rectorange" || operation == "RECTORANGE") {
                    M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(),
                             M5Cardputer.Display.height() - 28, ORANGE);
                    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4,
                             M5Cardputer.Display.width(), 4, ORANGE);
                }
                else if(operation == "text_PINK" || operation == "text_pink" || operation == "TEXT_pink" || operation == "TEXT_PINK" || operation == "textpink" || operation == "TEXTPINK") {
                    M5Cardputer.Display.setTextColor(TFT_PINK);
                } else if(operation == "rect_PINK" || operation == "rect_pink" || operation == "RECT_pink" || operation == "RECT_PINK" || operation == "rectpink" || operation == "RECTPINK") {
                    M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(),
                             M5Cardputer.Display.height() - 28, PINK);
                    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4,
                             M5Cardputer.Display.width(), 4, PINK);
                }
                else if(operation == "text_BLUE" || operation == "text_blue" || operation == "TEXT_blue" || operation == "TEXT_BLUE" || operation == "textblue" || operation == "TEXTBLUE") {
                    M5Cardputer.Display.setTextColor(TFT_BLUE);
                } else if(operation == "rect_BLUE" || operation == "rect_blue" || operation == "RECT_blue" || operation == "RECT_BLUE" || operation == "rectblue" || operation == "RECTBLUE") {
                    M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(),
                             M5Cardputer.Display.height() - 28, BLUE);
                    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4,
                             M5Cardputer.Display.width(), 4, BLUE);
                }
                else if(operation == "pi"){
                    canvas.println(3.14159265358979323846);
                } else if (operation == ":3"){
                    canvas.println(":3 :3 :3 :3 :3 :3 :3 :3 :3 :3 :3");
                    canvas.println("UwU");
                    canvas.println("Made by Jan Wilczek :3");
                }
                else {
                    calculate();
                    canvas.println(data + " = " + operation);
                }
                
                canvas.pushSprite(4, 4);
                data = "> ";
            }

            M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 28,
                                         M5Cardputer.Display.width(), 25,
                                         BLACK);

            M5Cardputer.Display.drawString(data, 4,
                                           M5Cardputer.Display.height() - 24);
        }
    }
}