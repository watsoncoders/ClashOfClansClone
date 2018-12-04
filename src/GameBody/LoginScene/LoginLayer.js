/**
 * Created by CPU02302_LOCAL on 12/4/2018.
 */


var LoginLayer = cc.Layer.extend({

    ctor:function () {
        this._super();
        this.init();
    },

    init: function(){

        var winSize = cc.director.getWinSize();

        var label = new cc.LabelTTF("Power by Cocos2d-JS", "Arial", 21);
        label.setColor(cc.color("#fff"));
        this.addChild(label);
        label.x = winSize.width  / 2;
        label.y = winSize.height / 2;

        return true;
    }
});

LoginLayer.scene = function() {
    var scene = new cc.Scene();
    var layer = new LoginLayer();
    scene.addChild(layer);
    return scene;
};