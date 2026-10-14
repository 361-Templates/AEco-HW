#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "AEWorld.h"
#include "Organism.h"
#include "emp/config/ArgManager.hpp"
#include "emp/prefab/ConfigPanel.hpp"
#include "emp/web/UrlParams.hpp"
#include "Config.h"

emp::web::Document doc("animation");
emp::web::Document settings("settings");
emp::web::Document buttons("buttons");
AEConfigBase config;

class AEAnimator : public emp::web::Animate {

// arena width and height
const int num_h_boxes = 100;
const int num_w_boxes = 100;
const double RECT_SIDE = 5;
const double width{num_w_boxes * RECT_SIDE};
const double height{num_h_boxes * RECT_SIDE};
emp::Random random{5};
AEWorld world{random, num_w_boxes, num_h_boxes};

        

// where we'll draw
emp::web::Canvas canvas{width, height, "canvas"};

public:

    AEAnimator() {
        // shove canvas into the div
        // along with a control button
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        // apply configuration query params and config files to config
        auto specs = emp::ArgManager::make_builtin_specs(&config);
        emp::ArgManager am(emp::web::GetUrlParams(), specs);
        
        am.UseCallbacks();
        if (am.HasUnused()) std::exit(EXIT_FAILURE);

        // setup configuration panel
        emp::prefab::ConfigPanel config_panel(config);
        settings << config_panel; 

        

    }

    

    void DoFrame() override {
        world.Update();
        emp::vector<emp::Ptr<Organism>> pop = world.GetFullPop();
        canvas.Clear();

        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++){
             for (int y = 0; y < num_h_boxes; y++) {

                if (world.IsOccupied(org_num)){
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "black", "black");
                } else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "green", "green");
                }
                org_num++;
            }
        }

    }


};

AEAnimator animator;

int main() {animator.Step();}