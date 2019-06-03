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
                                    ["children"] = {
                                        [1] = {
                                            ["children"] = {
                                                [1] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Condition_4",
                                                            ["func"] = "ai_canAttack",
                                                            ["arg"] = {
                                                                [1] = "",
                                                            },
                                                        },
                                                        [2] = {
                                                            ["type"] = "Action",
                                                            ["name"] = "Condition_5",
                                                            ["func"] = "ai_attackRangeTest",
                                                            ["arg"] = {
                                                                [1] = "",
                                                            },
                                                        },
                                                        [3] = {
                                                            ["children"] = {
                                                                [1] = {
                                                                    ["type"] = "Action",
                                                                    ["name"] = "Action_5",
                                                                    ["func"] = "ai_Skill",
                                                                    ["arg"] = {
                                                                        [1] = "",
                                                                    },
                                                                },
                                                            },
                                                            ["type"] = "RandomSelector",
                                                            ["name"] = "doSkill",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                                [1] = 1,
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Sequence",
                                                    ["name"] = "attack",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                        [1] = "",
                                                    },
                                                },
                                                [2] = {
                                                    ["children"] = {
                                                        [1] = {
                                                            ["type"] = "True",
                                                            ["name"] = "True_1",
                                                            ["func"] = "",
                                                            ["arg"] = {
                                                                [1] = "",
                                                            },
                                                        },
                                                    },
                                                    ["type"] = "Wait",
                                                    ["name"] = "Wait_2",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                        [1] = 5,
                                                    },
                                                },
                                            },
                                            ["type"] = "RandomSelector",
                                            ["name"] = "have target",
                                            ["func"] = "",
                                            ["arg"] = {
                                                [1] = 1,
                                                [2] = 1,
                                            },
                                        },
                                    },
                                    ["type"] = "Filter",
                                    ["name"] = "have target ????",
                                    ["func"] = "ai_hasTarget",
                                    ["arg"] = {
                                        [1] = 10,
                                        [2] = 20,
                                    },
                                },
                                [2] = {
                                    ["children"] = {
                                        [1] = {
                                            ["type"] = "Action",
                                            ["name"] = "do find target",
                                            ["func"] = "ai_findTarget",
                                            ["arg"] = {
                                                [1] = "",
                                            },
                                        },
                                        [2] = {
                                            ["children"] = {
                                                [1] = {
                                                    ["type"] = "Action",
                                                    ["name"] = "Action_1",
                                                    ["func"] = "ai_forward",
                                                    ["arg"] = {
                                                        [1] = "",
                                                    },
                                                },
                                                [2] = {
                                                    ["type"] = "Action",
                                                    ["name"] = "Action_2",
                                                    ["func"] = "ai_backAway",
                                                    ["arg"] = {
                                                        [1] = "",
                                                    },
                                                },
                                                [3] = {
                                                    ["type"] = "True",
                                                    ["name"] = "True_2",
                                                    ["func"] = "",
                                                    ["arg"] = {
                                                        [1] = "",
                                                    },
                                                },
                                            },
                                            ["type"] = "RandomSelector",
                                            ["name"] = "find target fail",
                                            ["func"] = "",
                                            ["arg"] = {
                                                [1] = 1,
                                                [2] = 1,
                                                [3] = 1,
                                            },
                                        },
                                    },
                                    ["type"] = "Selector",
                                    ["name"] = "no target",
                                    ["func"] = "",
                                    ["arg"] = {
                                        [1] = "",
                                    },
                                },
                            },
                            ["type"] = "Selector",
                            ["name"] = "Selector_1",
                            ["func"] = "",
                            ["arg"] = {
                                [1] = "",
                            },
                        },
                        [2] = {
                            ["children"] = {
                                [1] = {
                                    ["type"] = "Action",
                                    ["name"] = "Action_7",
                                    ["func"] = "ai_Wait",
                                    ["arg"] = {
                                        [1] = "",
                                    },
                                },
                            },
                            ["type"] = "Wait",
                            ["name"] = "Wait_1",
                            ["func"] = "",
                            ["arg"] = {
                                [1] = 2,
                            },
                        },
                    },
                    ["type"] = "RandomSelector",
                    ["name"] = "RandomSelector_1",
                    ["func"] = "",
                    ["arg"] = {
                        [1] = 1,
                        [2] = 1,
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