-- Scene script.
common = require("data/scripts/Common")
scene = {
    name = "Scene_01",
    version = "1.0.0",
    mode = "R25D",
    quit = false,
    setup = function(scene, camera)
        -- Init function callback.
        e = hpms.make_entity('data/out/01.hmdat')
        b = hpms.make_background('data/resources/textures/B01_B.png')
        d = hpms.make_depth_mask('data/resources/textures/B01_D.png')
        n = hpms.make_node("NODE_01")

        common.loc_rot_scale(e, 0, 0, 0, 0, 0, 0, 0.2, 0.2, 0.2)
        common.loc_rot_scale(n, -1, 0, 0, 0, 0, 0, 1, 1, 1)

        camera.position = hpms.vec3(3.5, 1, -3)
        camera.rotation = hpms.vec3(0, hpms.to_radians(-120), 0)
        scene.ambient_light = hpms.vec3(1, 1, 1)
        hpms.set_node_entity(n, e)
        hpms.add_node_to_scene(n, scene)

        --hpms.add_entity_to_scene(e, scene)
        hpms.add_picture_to_scene(b, scene)
        hpms.add_picture_to_scene(d, scene)
    end,
    input = function(keys)
        speed = 0
        rotate = 0


        -- Input function callback.

        if keys ~= nil then
            -- print(key.key)
            if hpms.action_performed(keys, 'ESC', common.PRESSED) then
                scene.quit = true
            end
            if hpms.action_performed(keys, 'UP', common.PRESSED) then
                speed = 1
            elseif hpms.action_performed(keys, 'DOWN', common.PRESSED) then
                speed = -1
            else
                speed = 0
            end

            if hpms.action_performed(keys, 'RIGHT', common.PRESSED) then
                rotate = -1
            elseif hpms.action_performed(keys, 'LEFT', common.PRESSED) then
                rotate = 1
            else
                rotate = 0
            end
        end
    end,
    update = function(scene, camera)
        -- Update loop function callback.
        common.move_towards_direction(n, speed / 120.0)
        common.rotate(n, 0, rotate / 3.0, 0)
    end,
    cleanup = function()
        -- Close function callback.
        hpms.delete_node(n)
        hpms.delete_entity(e)
        hpms.delete_background(b)
        hpms.delete_depth_mask(d)
    end
}