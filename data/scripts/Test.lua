-- Scene script.
scene = {
    name = "Scene_01",
    version = "1.0.0",
    data = "Scene_01.hdat",
    mode = "R25D",
    quit = false,
    setup = function(scene, camera)
        -- Init function callback.
    end,
    input = function(key)
        if key ~= nil then
            if key.key == 'ESC' then
                scene.quit = true
            end
        end
        -- Input function callback.
    end,
    update = function(scene, camera)
        -- Update loop function callback.
    end,
    cleanup = function()
        -- Close function callback.
    end
}