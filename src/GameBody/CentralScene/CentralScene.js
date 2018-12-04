/**
 * Created by CPU02302_LOCAL on 12/4/2018.
 */

// Get Central Layer

var CentralScene = cc.Class.extend({

    ctor: function() {

        this.init();
    },

    init: function() {

        return true;
    }



});

CentralScene.create = function() {
    var scene = new CentralLayer.scene();
    return scene;
}