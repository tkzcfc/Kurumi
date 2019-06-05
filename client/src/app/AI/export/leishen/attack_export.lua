return {
    ["title"] = "new Tree",
    ["nodes"] = {
        [1] = {
            ["func"] = "",
            ["children"] = {
                [1] = {
                    ["children"] = {
                        [1] = {
                            ["children"] = {
                                [1] = {
                                    ["type"] = "Action",
                                    ["name"] = "Action_1",
                                    ["func"] = "ai_do_handle",
                                    ["arg"] = {
                                        [1] = "CMD_Skill1",
                                        [2] = true,
                                    },
                                },
                            },
                            ["type"] = "Wait",
                            ["name"] = "Wait_1",
                            ["func"] = "",
                            ["arg"] = {
                                [1] = 5,
                            },
                        },
                    },
                    ["type"] = "Sequence",
                    ["name"] = "Sequence_1",
                    ["func"] = "",
                    ["arg"] = {
                        [1] = "",
                    },
                },
            },
            ["type"] = "Start",
            ["name"] = "",
            ["arg"] = {
                [1] = "",
            },
        },
    },
}