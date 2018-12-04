/**
 * Created by CPU02302_LOCAL on 12/4/2018.
 */

//Init UserData -> Check exist User -> Get UserData -> Get Login Layer

var LoginScene = cc.Class.extend({

    ctor: function() {

        this.init();
    },

    init: function() {

        return true;
    }



});

LoginScene.create = function() {
    var scene = new LoginLayer.scene();
    return scene;
}