/**
 * Created with JetBrains WebStorm.
 * User: lihex
 * Date: 12-8-9
 * Time: 上午9:53
 * To change this template use File | Settings | File Templates.
 */

require("../../system/Log");

module.exports.handler = function (req, res, next) {
    var log = new Log("getBasicInfo");

    var chunks = [];
    req.on("data", function (chunk) {
        chunks.push(chunk);
    });
    req.on("end", function () {
        var info = JSON.parse(Buffer.concat(chunks));
        chunks = undefined;
        log.d("request:", info);

        var responseResult = function (ret) {
            var respData = {};
            var out = ret;
            var header = info.header;
            var meta = info.meta;
            respData.heard = header;
            respData.meta = meta;
            respData.meta.out = out;
            respData.meta.result = 0;
            log.d("responseResult", respData);
            res.write(JSON.stringify(respData));
            res.end();
        };

        if (info) {
            var uuid = parseInt(info.header.token);
            var actor = require("../Actors").getActor(uuid);
            if(null != actor){
                responseResult(actor.getBasicInfo());
            }
        } else {
            next();
        }

    });
};