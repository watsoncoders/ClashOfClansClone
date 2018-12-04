/**
 * Created by CPU02302_LOCAL on 12/4/2018.
 */

var SceneManager = cc.Class.extend({

    centralScene: false,
    loginScene: false


});

SceneManager.runScene = function(sceneID) {

    var scene = null;

    switch (sceneID){
        case "SCENE_LOGIN":
            scene = LoginScene.create();
            break;
        case "SCENE_CENTRAL":
            scene = CentralScene.create();
            break;
        default:
            scene =  LoginScene.create();
    }
    return scene;

};