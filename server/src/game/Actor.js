/**
 * Actor model.
 */

require("../system/Class");
require("../system/Log");


Actor = Class.extend({
    _db: {},                // actor database
    _tdb: {},               // actor temporary database, will not sync to database

    init: function(dbData) {
        if (dbData) {
            this._db = dbData;
        } else {
            this.initDefaultData();
        }
    },

    initDefaultData: function(){
        var db = this._db;
        db.exp = 0;
    },

    getBasicInfo:function () {
        var db = this._db;
        var ret = {};
        ret.nickname = db.nickname;
        ret.image_id = db.image_id;
        ret.level = db.level;
        ret.exp = db.exp;
        ret.hp = db.hp;
        ret.career_id = db.career_id;
        ret.chapter_id = db.chapter_id;
        ret.page_id = db.page_id;
        return ret;
    },

    getEquipment:function(part) {
        var log = new Log("actor.getEquipmentInfo");
        log.d(part);
        var db = this._db;
        var equipment = require("./ActorEquipments").getEquipment(db.id);
    }
});
