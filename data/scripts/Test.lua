-- Scene script.
scene = {
    name = "Scene_01",
    version = "1.0.0",
    data = "Scene_01.hdat",
    mode = "R25D",
    quit = false,
    setup = function(scene, camera)
        -- Init function callback.
        e = hpms.make_entity('data/out/01.hdat')
        b = hpms.make_background('data/resources/textures/B01_B.png')
        d = hpms.make_depth_mask('data/resources/textures/B01_D.png')
        e.position = hpms.vec3(0, 0, 0)
        e.rotation = hpms.from_axis(0, 0, 0, 1)
        e.scale = hpms.vec3(0.2, 0.2, 0.2)

        camera.position = hpms.vec3(3.5, 1, -3)
        camera.rotation = hpms.vec3(0, hpms.to_radians(-120), 0)
        scene.ambient_light = hpms.vec3(1, 1, 1)
        hpms.add_entity_to_scene(e, scene)
        hpms.add_picture_to_scene(b, scene)
        hpms.add_picture_to_scene(d, scene)
    end,
    input = function(key)
        -- Input function callback.
        if key ~= nil then
            if key.key == 'ESC' then
                scene.quit = true
            end
        end
    end,
    update = function(scene, camera)
        -- Update loop function callback.
    end,
    cleanup = function()
        -- Close function callback.
        hpms.delete_entity(e)
        hpms.delete_background(b)
        hpms.delete_depth_mask(d)
    end
}